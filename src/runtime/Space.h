#ifndef __EASY_PYTHON_VM_SPACE_H_
#define __EASY_PYTHON_VM_SPACE_H_
#include <memory.h>
#include <stdlib.h>
namespace easy_vm{

//表示虚拟机可使用的一块空间
class Space{
friend class Heap;
public:
   void* allocate(size_t size);
   void  clear();
   bool  canAllocate(size_t size);
   bool  hasObj(char* obj);//判断该空间内是否存在某对象
private:
   Space(size_t size); 
   ~Space();
private:
   char* m_base;//空间的起始地址
   char* m_top; //可用内存的开始地址
   char* m_end; //空间的结束地址
   size_t m_size;//总容量    
   size_t m_capacity;//可用容量
};


//表示堆空间
class Heap{
public:
   ~Heap();
   static size_t MAX_CAP;//堆的最大容量
   static Heap* instance; //堆采用单例模式
   static Heap* getInstance();
public:
   void* allocate(size_t size);//分配空间
   void* allocateMeta(size_t size);//分配元数据空间，存储类型信息
   void  copyLiveObjects();//复制存活对象，进行垃圾回收
   void  gc();
private:
   Heap(size_t size);
private:
   //堆区使用标记复制算法来回收垃圾，因此整个堆区划分为两半
   Space* mem_1;//
   Space* mem_2;
   Space* eden;
   Space* survivor;
   Space* metaspace;
   
};

} 

#endif