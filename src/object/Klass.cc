#include "Klass.h"
#include "method.h"
#include "../runtime/universe.h"
#include <iostream>
namespace easy_vm{

Object* Klass::getattr(Object* obj,Object* attr){
   Object* result = Universe::None;
   result = getKlassDict()->get(attr);
   if(result == Universe::None){
       std::cout << "warning:attr: ";
       attr->print();
       std::cout << "not find" <<std::endl;
       return result;
   }
   if(Method::isFunction(result)){
       result = new Method(static_cast<Function*>(result),obj);
   }
   return result;
}

Object* Klass::setattr(Object* obj,Object* attr,Object* value){

}

//0表示类型相同，小于0表示kls1的类型小于kls2的类型，大于0反之
int Klass::compareKlass(Klass* kls1,Klass* kls2){
    if(kls1 == kls2){
        return 0;
    }
    if(kls1 == IntegerKlass::getInstance()){
        //Python规定 Integer的类型是最小
        return -1;
    }else if(kls2 == IntegerKlass::getInstance()){
        return 1;
    }

    if(kls1->getName()->less(kls2->getName()) == Universe::True){
        return -1;
    }else{
        return 1;
    }
}

Object* Klass::createKlass(Object* attrs,Object* supers,Object* name){
    assert(attrs && attrs->klass() == DictKlass::getInstance());
    assert(supers && supers->klass() == ListKlass::getInstance());
    assert(name && name->klass() == StringKlass::getInstance());
    Klass* newKlass = new Klass();
    Dict* klassAttr = static_cast<Dict*>(attrs);
    List* klassSupers = static_cast<List*>(supers);
    newKlass->setKlassDict(klassAttr);
    newKlass->setName(static_cast<String*>(name));
    if(klassSupers->getList()->size() > 0){
        Type* super = static_cast<Type*>(klassSupers->get(0));
        newKlass->setSuper(super->getOwnKlass());
    }
    Type* type = new Type();
    type->setOwnKlass(newKlass);
    return type;
}

Object* Klass::allocateInstance(Object* objType,std::vector<Object*>* args){
    Object* inst = new Object();
    inst->setKlass(static_cast<Type*>(objType)->getOwnKlass());
    return inst; 
}

}