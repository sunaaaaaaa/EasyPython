#include "integer.h"
#include<iostream>
namespace easy_vm{

void Integer::print(){
   std::cout << m_value <<std::endl; 
}

Object* Integer::add(Object* obj){
   return new Integer(m_value + ((Integer*)obj)->m_value);
}
}