#include "object.h"
#include "dict.h"
#include "method.h"
#include "string_table.h"
#include "../runtime/universe.h"
#include <iostream>
namespace easy_vm{

ObjectKlass* ObjectKlass::instance = NULL;

ObjectKlass* ObjectKlass::getInstance(){
   if(instance == NULL){
      instance = new ObjectKlass();
      init(instance);
   }
   return instance;
}

ObjectKlass::ObjectKlass(){
}

void ObjectKlass::init(Klass* kls){
   kls->setSuper(NULL);
   Dict* d  = new Dict();
   kls->setKlassDict(d);
   kls->setName(new String("object"));
   Type* type = new Type();
   type->setOwnKlass(kls);
}

void Object::initObjAttr(){ m_objAttr = new Dict();}

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

TypeKlass* TypeKlass::instance = NULL;

TypeKlass* TypeKlass::getInstance(){
   if(instance == NULL){
      instance = new TypeKlass();
      init(instance);
   }
   return instance;
}

void TypeKlass::init(Klass* kls){
   kls->setName(new String("type"));
   kls->setSuper(ObjectKlass::getInstance());
   Type* type = new Type();
   type->setOwnKlass(kls); 
}

void TypeKlass::print(Object* obj){
   assert(obj->klass() == static_cast<Klass*>(this));
   std::cout << "<type:";
   Klass* ownklass = static_cast<Type*>(obj)->getOwnKlass();
   Dict* dict = ownklass->getKlassDict();
   if(dict){
      Object* mod = dict->get(static_cast<Object*>(StringTable::getInstance()->mod));
      if(mod != Universe::None){
         mod->print();
         std::cout << ".";
      }
   }
   ownklass->getName()->print();
   std::cout << ">" <<std::endl;
}

Object* TypeKlass::getattr(Object* obj,Object* attr){
   Type* type = static_cast<Type*>(obj);
   Object* result = Universe::None;
   result = type->getOwnKlass()->getKlassDict()->get(attr);
   if(result == Universe::None){
       std::cout << "warning:attr: ";
       attr->print();
       std::cout << "not find" <<std::endl;
       return result;
   }
   // if(Method::isFunction(result)){
   //     result = new Method(static_cast<Function*>(result),obj);
   // }
   return result; 
}

Object* TypeKlass::setattr(Object* obj,Object* attr,Object* value){
   Type* type = static_cast<Type*>(obj);
   type->getOwnKlass()->getKlassDict()->put(attr,value);
   return Universe::None;
}


Type::Type(){
   setKlass(TypeKlass::getInstance());
}
//完成Klass与该Klass对应Type的绑定
void Type::setOwnKlass(Klass* kls){
   m_own_klass = kls;
   kls->setType(this);
}

}