#include "object.h"

namespace easy_vm{

void Object::print(){
   if(m_klass!=NULL){
      m_klass->print(this);
   }  
}

Object* Object::len(){
   assert(m_klass!=NULL);
   return m_klass->len(this);
}

Object* Object::add(Object* obj){
   assert(m_klass!=NULL);
   m_klass->add(this,obj);
}
Object* Object::sub(Object* obj){
   assert(m_klass!=NULL);
   m_klass->sub(this,obj);
}
Object* Object::mul(Object* obj){
   assert(m_klass!=NULL);
   m_klass->mul(this,obj);
}
Object* Object::div(Object* obj){
   assert(m_klass!=NULL);
   m_klass->div(this,obj);
}
Object* Object::mod(Object* obj){
   assert(m_klass!=NULL);
   m_klass->mod(this,obj);
}
Object* Object::greater(Object* obj){
   assert(m_klass!=NULL);
   m_klass->greater(this,obj);
}
Object* Object::less(Object* obj){
   assert(m_klass!=NULL);
   m_klass->less(this,obj);
}
Object* Object::equal(Object* obj){
   assert(m_klass!=NULL);
   m_klass->equal(this,obj);
}
Object* Object::not_equal(Object* obj){
   assert(m_klass!=NULL);
   m_klass->not_equal(this,obj);
}
Object* Object::ge(Object* obj){
   assert(m_klass!=NULL);
   m_klass->ge(this,obj);
}
Object* Object::le(Object* obj){
   assert(m_klass!=NULL);
   m_klass->le(this,obj);
}

}