#include "Space.h"
#include "../memory/oopClosure.h"
#include <iostream>
namespace easy_vm{

Space::Space(size_t size):m_size(size){
    m_base = (char*)malloc(size);
    m_end = m_base + size;
    //内存对齐，保证地址空间以16字节对齐
    m_top = (char*)(((long)(m_base + 15)) & -16);
    m_capacity = m_end - m_top;
}

Space::~Space(){
    if(m_base){
        free(m_base);
        m_base = 0;
    }
    m_top = 0;
    m_end = 0;
    m_size = 0;
    m_capacity = 0;
}

void* Space::allocate(size_t size){
    //保证堆分配的对象以8字节对齐
    size = (size + 7) & -8;
    char* start = m_top;
    m_top += size;
    m_capacity -= size;
    return start;
}

void Space::clear(){
    memset(m_base,0,m_size);
    m_top = (char*)(((long)(m_base + 15)) & -16);
    m_capacity = m_end - m_top;
}

bool Space::canAllocate(size_t size){
    return m_capacity > size;
}

bool Space::hasObj(char* obj){
    return obj >= m_base && m_end > obj;
}


Heap* Heap::instance = NULL;
size_t Heap::MAX_CAP = 2 * 1024 * 1024;

Heap* Heap::getInstance(){
    if(instance == NULL){
        instance = new Heap(MAX_CAP);
    }
    return instance;
}

Heap::Heap(size_t size){
   mem_1 = new Space(size);
   mem_2 = new Space(size);
   metaspace = new Space(size / 16);
   mem_1->clear();
   mem_2->clear();
   metaspace->clear();
   eden = mem_1;
   survivor = mem_2; 
}

Heap::~Heap(){
   if(mem_1){
       delete mem_1;
       mem_1 = NULL;
   }
   if(mem_2){
       delete mem_2;
       mem_2 = NULL;
   }
   if(metaspace){
       delete metaspace;
       metaspace = NULL;
   }
   eden = NULL;
   survivor = NULL;
}

void* Heap::allocate(size_t size){
    //如果eden区放不下，则先清理垃圾
    if(!eden->canAllocate(size)){
        gc();
    }
    return eden->allocate(size);
}

//元数据区不进行垃圾回收
void* Heap::allocateMeta(size_t size){
    if(!metaspace->canAllocate(size)){
        return NULL;
    }
    return metaspace->allocate(size);
}

//复制存活对象，交换eden与survivor指针
void Heap::copyLiveObjects(){
    ScanvengeOopClosure closure(eden,survivor,metaspace);
    closure.scavenge();
}

void Heap::gc(){
   std::cout << "gc starting..."<<std::endl;
   std::cout << "before gc:"<<std::endl;
   std::cout << "eden capacity is " << eden->m_capacity << std::endl;
   copyLiveObjects();

   Space* t = eden;
   eden = survivor;
   survivor = t;
   std::cout << "after gc:"<<std::endl;
   std::cout << "eden capacity is " << eden->m_capacity << std::endl;
   std::cout << "gc end" << std::endl;
   survivor->clear();
}

}