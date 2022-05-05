#include "List.h"
#include "Klass.h"
#include "method.h"
#include "string_table.h"
#include "../runtime/universe.h"
#include "../runtime/interpreter.h"
#include <vector>
#include <algorithm>
#include <iostream>
namespace easy_vm{

Klass::Klass():m_super(NULL),m_mro(NULL),m_name(NULL),m_klass_dict(NULL){
    Universe::klasses->push_back(this);
}


void Klass::addSuper(Klass* super){
    if(m_super == NULL){
        m_super = new List();
    }
    m_super->append(super->getType());
}


void Klass::orderSuper(){
    if(m_super == NULL){
        return;
    }
    if(m_mro == NULL){
        m_mro = new List();
    }

    int cur = -1;
    for(int i = 0;i<m_super->size();++i){
        Type* type = static_cast<Type*>(m_super->get(i));
        Klass* kls = type->getOwnKlass();
        m_mro->append(type);
        //如果当前父类没有父类，则处理下一个父类
        if(kls->m_mro == NULL){
            continue;
        }
        //查找父类的超类是否已经存储过了，如果重复存储则将前面的删除，保留后面的
        for(int j = 0;j<kls->m_mro->size();++j){
            Type* type = static_cast<Type*>(kls->m_mro->get(i));
            int index = m_mro->index(type);
            if(index < cur){
                std::cout << "Error:method resolution order conflicts"<<std::endl;
                assert(false);
            }
            cur = index;
            if(index >= 0){
                m_mro->deleteIndex(index);
            }
            m_mro->append(type);
        }
    }

    if(m_mro == NULL){
        return;
    }
    std::cout <<m_name->value() <<" mro is:";
    for(int i = 0;i<m_mro->size();++i){
        Type* type = static_cast<Type*>(m_mro->get(i));
        Klass* kls = type->getOwnKlass();
        std::cout <<kls->getName()->value() <<"  ";
    }
    std::cout <<std::endl;
}

void* Klass::operator new(size_t size){
    // void* temp = Universe::heap->allocateMeta(size);
    // return temp;
    return Universe::heap->allocateMeta(size);
}

void Klass::oops_do(OopClosure* closure, Object* obj) {
    std::cout << "warning: klass oops_do for ";
    m_name->print();
    std::cout << std::endl;
}

Object* Klass::findAttr(Object* obj,Object* attr){
    //默认逻辑
    Object* result = Universe::None;
    //先找对象存储的属性
    if(obj->getObjAttr()!=NULL){
        result = obj->getObjAttr()->get(attr);
        if(result != Universe::None){
            return result;
        }
    }
    result = findAttrInParent(obj,attr);
    if(Method::isFunction(result)){
       result = new Method(static_cast<Function*>(result),obj);
    }
    return result;
}

//从当前类型以及父类型中寻找
Object* Klass::findAttrInParent(Object* obj,Object* attr){
    Object* result = Universe::None;
    result = getKlassDict()->get(attr);
    if(result != Universe::None){
        return result;
    }
    
    //直接父类找不到则从父类的父类中寻找
    if(obj->klass()->getMro() == NULL){
        return result;
    }
    
    List* parentKls = obj->klass()->getMro();
    for(int i = 0;i<parentKls->size();++i){
        result = static_cast<Type*>(parentKls->get(i))->getOwnKlass()->getKlassDict()->get(attr);
        if(result != Universe::None){
            break;
        }
    }
    
    if(result == Universe::None){
        std::cout << "warning:attr: ";
        attr->print();
        std::cout << "not find an where(include parent class)" <<std::endl;
    }
    return result;
}

Object* Klass::getattr(Object* obj,Object* attr){
   //如果类型重写了__getattr__函数，则执行__getattr__函数
   if(obj==Universe::None){
       return Universe::None;
   }
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
   result = findAttrInParent(obj,attr);
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
        for(int i = 0;i<klassSupers->getList()->size();++i){
           Type* super = static_cast<Type*>(klassSupers->get(i));
           newKlass->addSuper(super->getOwnKlass());
        }
        newKlass->orderSuper(); 
    }
    Type* type = new Type();
    type->setOwnKlass(newKlass);
    return type;
}

Object* Klass::allocateInstance(Object* objType,std::vector<Object*>* args){
    Object* inst = new Object();
    inst->setKlass(static_cast<Type*>(objType)->getOwnKlass());
    //看该对象所属的Klass是否定义了__init__函数，如果定义了则执行,所有内置类型都重写了该方法，因此不会执行
    Object* construct = inst->findAttr(StringTable::getInstance()->init);
    if(construct != Universe::None){
        Interpreter::getInstance()->callVitrual(construct,args);
    }else{
        std::cout <<"use default construct create an object"<<std::endl;
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