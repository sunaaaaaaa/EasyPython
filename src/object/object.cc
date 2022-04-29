#include "object.h"

namespace easy_vm{

void Object::print(){
   if(m_klass!=NULL){
      m_klass->print(this);
   }  
}

Object* Object::add(Object* obj){
   m_klass->add(this,obj);
}
Object* Object::sub(Object* obj){
   m_klass->sub(this,obj);
}
Object* Object::mul(Object* obj){
   m_klass->mul(this,obj);
}
Object* Object::div(Object* obj){
   m_klass->div(this,obj);
}
Object* Object::mod(Object* obj){
   m_klass->mod(this,obj);
}
Object* Object::greater(Object* obj){
   m_klass->greater(this,obj);
}
Object* Object::less(Object* obj){
   m_klass->less(this,obj);
}
Object* Object::equal(Object* obj){
   m_klass->equal(this,obj);
}
Object* Object::not_equal(Object* obj){
   m_klass->not_equal(this,obj);
}
Object* Object::ge(Object* obj){
   m_klass->ge(this,obj);
}
Object* Object::le(Object* obj){
   m_klass->le(this,obj);
}

}