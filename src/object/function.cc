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
    setKlass(FunctionKlass::getInstance());
}

Function::Function(Klass* klass){
    m_funcName = NULL;
    m_codes = NULL;
    m_flags = 0;
    setKlass(FunctionKlass::getInstance());
}

}