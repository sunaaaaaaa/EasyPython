#include "integer.h"
#include "../runtime/universe.h"
#include<iostream>
namespace easy_vm{

void Integer::print(){
   std::cout << m_value <<std::endl; 
}

Object* Integer::add(Object* obj){
   return new Integer(m_value + ((Integer*)obj)->m_value);
}


Object* Integer::greater(Object* obj){
   if(m_value > ((Integer*)obj)->m_value){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* Integer::less(Object* obj){
    if(m_value > ((Integer*)obj)->m_value){
      return Universe::False;
   }else{
      return Universe::True;
   }
}
Object* Integer::equal(Object* obj){
    if(m_value == ((Integer*)obj)->m_value){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* Integer::not_equal(Object* obj){
    if(m_value != ((Integer*)obj)->m_value){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* Integer::ge(Object* obj){
    if(m_value >= ((Integer*)obj)->m_value){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* Integer::le(Object* obj){
    if(m_value <= ((Integer*)obj)->m_value){
      return Universe::True;
   }else{
      return Universe::False;
   }
}

}