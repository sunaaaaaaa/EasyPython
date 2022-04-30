#include "method.h"

namespace easy_vm{

MethodKlass* MethodKlass::instance = NULL;

MethodKlass* MethodKlass::getInstance(){
    if(instance == NULL){
        instance = new MethodKlass();
    }
    return instance;
}

void MethodKlass::print(Object* obj){

}

bool Method::isFunction(Object* obj){
    Klass* klass = obj->klass();
    if(klass != FunctionKlass::getInstance()){
        return false;
    }
    Function* func = static_cast<Function*>(obj);
    return ((func->flags() & Function::CO_GENERATOR) != 0);
}

}