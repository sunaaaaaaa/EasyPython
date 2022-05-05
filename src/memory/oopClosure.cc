#include "oopClosure.h"
#include "../object/object.h"
#include "../util/stack.h"
#include <iostream>
namespace easy_vm{

ScanvengeOopClosure::ScanvengeOopClosure(Space* from, Space* to, Space* meta):m_from(from),m_to(to),m_meta(meta){
    m_oop_stack = new Stack<Object*>(1024);
}

ScanvengeOopClosure::~ScanvengeOopClosure() {
    m_from = NULL;
    m_to = NULL;
    delete m_oop_stack;
    m_oop_stack = NULL;
}

void ScanvengeOopClosure::scavenge(){
   //标记根节点
   process_roots();
   //处理复制存活对象
   while(!m_oop_stack->empty()){
    //    m_oop_stack->pop()->oops_do(this);
     Object* temp = m_oop_stack->pop();
     temp->oops_do(this);
   }
}


 void ScanvengeOopClosure::process_roots(){

 }

void ScanvengeOopClosure::do_oop(Object** obj){

}

void ScanvengeOopClosure::do_array_list(ArrayList<Klass*>** list){

}

void ScanvengeOopClosure::do_array_list(ArrayList<Object*>** list){

}

void ScanvengeOopClosure::do_map(Map<Object*,Object*>** map){

}

void ScanvengeOopClosure::do_raw_mem(char** mem,int length){

}

void ScanvengeOopClosure::do_klass(Klass** kls){
    
}

}