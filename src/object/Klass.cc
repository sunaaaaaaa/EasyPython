#include "Klass.h"
#include "method.h"
#include "string_table.h"
#include "../runtime/universe.h"
#include "../runtime/interpreter.h"
#include <vector>
#include <iostream>
namespace easy_vm{

Object* Klass::getattr(Object* obj,Object* attr){
   //如果类型重写了__getattr__函数，则执行__getattr__函数
   Object* func = obj->klass()->getKlassDict()->get(StringTable::getInstance()->getattr);
   if(func != Universe::None && func->klass()==FunctionKlass::getInstance()){
       func = new Method(static_cast<Function*>(func),obj);
       std::vector<Object*>* args = new std::vector<Object*>();
       args->push_back(attr);
       return Interpreter::getInstance()->callVitrual(func,args);
   }  
   //默认逻辑
   Object* result = Universe::None;
   //先找对象存储的属性
   if(obj->getObjAttr()!=NULL){
       result = obj->getObjAttr()->get(attr);
       if(result != Universe::None){
           return result;
       }
   }
   //如果未对属性进行过更改，则从类型中寻找 
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
   //增加重载逻辑，如果对象重写了__setattr__函数，则执行该函数，否则放入ObjAttr字典中
   Object* func = getKlassDict()->get(StringTable::getInstance()->setattr);

   if(func != Universe::None && func->klass()==FunctionKlass::getInstance()){
       func = new Method(static_cast<Function*>(func),obj);
       std::vector<Object*>* args = new std::vector<Object*>();
       args->push_back(attr);
       args->push_back(value);
       return Interpreter::getInstance()->callVitrual(func,args);
   }
   //默认逻辑，放入ObjAttr字典
   if(obj->getObjAttr() == NULL){
       obj->initObjAttr();
   }
   obj->getObjAttr()->put(attr,value);
   return Universe::None;
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
    //看该对象所属的Klass是否定义了__init__函数，如果定义了则执行,所有内置类型都重写了该方法，因此不会执行
    Object* construct = inst->getattr(StringTable::getInstance()->init);
    if(construct != Universe::None){
        Interpreter::getInstance()->callVitrual(construct,args);
    } 
    return inst; 
}

Object* Klass::findAndCall(Object* obj,std::vector<Object*>* args,Object* funcName){
    Object* func = obj->getattr(funcName);
    if(func != Universe::None){
        return Interpreter::getInstance()->callVitrual(func,args);
    }
    std::cout << "class: ";
    obj->klass()->m_name->print();
    std::cout << " Error:unsupport operation for class" << std::endl;
    assert(false);
    return Universe::None;
}

Object* Klass::subscr(Object* obj,Object* index){
   std::vector<Object*>* args = new std::vector<Object*>();
   args->push_back(index);
   return findAndCall(obj,args,StringTable::getInstance()->getitem);
}

void Klass::storeSubscr(Object* obj,Object* index,Object* value){
   std::vector<Object*>* args = new std::vector<Object*>();
   args->push_back(index);
   args->push_back(value);
   findAndCall(obj,args,StringTable::getInstance()->setitem);
}

void Klass::delSubscr(Object* obj,Object* ele){
   
}

//如果自定义类型通过__add__重载加法运算，则会调用此add方法，内置类型都重写了该方法
Object* Klass::add(Object* obj1,Object* obj2){
   std::vector<Object*>* args = new std::vector<Object*>();
   args->push_back(obj2);
   return findAndCall(obj1,args,StringTable::getInstance()->add);
}

}