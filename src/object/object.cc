#include "object.h"

namespace easy_vm{

Object* Object::getattr(Object* attr){
   assert(m_klass != NULL);
   return m_klass->getattr(this,attr); 
}

Object* Object::setattr(Object* attr,Object* value){
   assert(m_klass != NULL);
   return m_klass->setattr(this,attr,value);  
}

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
   return m_klass->add(this,obj);
}
Object* Object::sub(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->sub(this,obj);
}
Object* Object::mul(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->mul(this,obj);
}
Object* Object::div(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->div(this,obj);
}
Object* Object::mod(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->mod(this,obj);
}
Object* Object::greater(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->greater(this,obj);
}
Object* Object::less(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->less(this,obj);
}
Object* Object::equal(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->equal(this,obj);
}
Object* Object::not_equal(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->not_equal(this,obj);
}
Object* Object::ge(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->ge(this,obj);
}
Object* Object::le(Object* obj){
   assert(m_klass!=NULL);
   return m_klass->le(this,obj);
}

Object* Object::subscr(Object* index){
   assert(m_klass != NULL);
   return m_klass->subscr(this,index);
}

void Object::storeSubscr(Object* index,Object* value){
   assert(m_klass != NULL);
   m_klass->storeSubscr(this,index,value);
}

void Object::delSubscr(Object* ele){
   assert(m_klass != NULL);
   m_klass->delSubscr(this,ele);
}

Object* Object::contains(Object* obj){
   assert(m_klass != NULL);
   return m_klass->contains(this,obj);
}

Object* Object::iter(){
   assert(m_klass != NULL);
   return m_klass->iter(this);
}

}