#include "function.h"
#include <iostream>
#include <assert.h>
namespace easy_vm{

FunctionKlass* FunctionKlass::instance = NULL;

FunctionKlass* FunctionKlass::getInstance(){
    if(instance == NULL){
        instance = new FunctionKlass();
    }
    return instance;
}

void FunctionKlass::print(Object* obj){
    std::cout << "<function: ";
    Function* func = static_cast<Function*>(obj);
    assert(func && func->klass()==static_cast<Klass*>(this));
    func->funcName()->print();
    std::cout << ">" <<std::endl;
}

Function::Function(Object* obj){
    CodeObject* codes = static_cast<CodeObject*>(obj);
    m_codes = codes;
    m_funcName = codes->m_co_name;
    m_flags = codes->m_flag;
    m_defaults = NULL;
    setKlass(FunctionKlass::getInstance());
}

Function::Function(Klass* klass){
    m_funcName = NULL;
    m_codes = NULL;
    m_flags = 0;
    m_defaults = NULL;
    setKlass(FunctionKlass::getInstance());
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

}