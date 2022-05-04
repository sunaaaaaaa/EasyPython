#include "function.h"
#include "../runtime/universe.h"
#include <iostream>
#include <assert.h>
namespace easy_vm{

FunctionKlass* FunctionKlass::instance = NULL;
NativeFunctionKlass* NativeFunctionKlass::instance = NULL;

FunctionKlass* FunctionKlass::getInstance(){
    if(instance == NULL){
        instance = new FunctionKlass();
    }
    return instance;
}

FunctionKlass::FunctionKlass(){
    addSuper(ObjectKlass::getInstance());
    setName(new String("function"));
    Type* type = new Type();
    type->setOwnKlass(this);
}

void FunctionKlass::print(Object* obj){
    std::cout << "<function: ";
    Function* func = static_cast<Function*>(obj);
    assert(func && func->klass()==static_cast<Klass*>(this));
    func->funcName()->print();
    std::cout << ">" <<std::endl;
}

NativeFunctionKlass* NativeFunctionKlass::getInstance(){
    if(instance == NULL){
        instance = new NativeFunctionKlass();
    }
    return instance;
}

Function::Function(Object* obj){
    CodeObject* codes = static_cast<CodeObject*>(obj);
    m_codes = codes;
    m_funcName = codes->m_co_name;
    m_flags = codes->m_flag;
    m_global = NULL;
    m_defaults = NULL;
    setKlass(FunctionKlass::getInstance());
}

Function::Function(Klass* klass){
    m_funcName = NULL;
    m_codes = NULL;
    m_flags = 0;
    m_global = NULL;
    m_defaults = NULL;
    setKlass(FunctionKlass::getInstance());
}

Function::Function(NativeFuncPointer nativeFunc){
    m_codes = NULL;
    m_funcName = NULL;
    m_flags = 0;
    m_global = NULL;
    m_defaults = NULL;
    m_native_func = nativeFunc;
    setKlass(NativeFunctionKlass::getInstance());
}

void Function::setDefaults(std::vector<Object*>* defaults){
    if(defaults == NULL){
        m_defaults = NULL;
        return;
    }
    m_defaults = new std::vector<Object*>();
    for(int i = 0;i< defaults->size();++i){
        //m_defaults->insert(m_defaults->begin()+i,defaults->at(i));
        m_defaults->push_back(defaults->at(i));
    }
}

Object* Function::call(std::vector<Object*>* args){
    return (*m_native_func)(args);
}

//-------------------------------------------------------------内置函数实现--------------------------------------------------//

Object* len(std::vector<Object*>* args){
    return args->at(0)->len();
}

Object* isInstance(std::vector<Object*>* args){
    assert(args->size()==2);
    Object* obj = args->at(0);//对象
    Object* ty = args->at(1);//类型
    assert(ty && ty->klass() == TypeKlass::getInstance());
    Klass* objType = obj->klass();
    
    if(objType->getType() == static_cast<Type*>(ty)){
        return Universe::True;
    }
    for(int i = 0;i<objType->getMro()->size();++i){
        if(objType->getMro()->get(i) == static_cast<Type*>(ty)){
            return Universe::True;
        }
    }
    return Universe::False; 
}

Object* type(std::vector<Object*>* args){
   Object* obj = args->at(0);
   return obj->klass()->getType();
}

}