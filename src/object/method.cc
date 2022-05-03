#include "method.h"
#include <iostream>
namespace easy_vm{

MethodKlass* MethodKlass::instance = NULL;

MethodKlass* MethodKlass::getInstance(){
    if(instance == NULL){
        instance = new MethodKlass();
    }
    return instance;
}

MethodKlass::MethodKlass(){
    setKlassDict(new Dict());
    setSuper(ObjectKlass::getInstance());
    setName(new String("method"));
    Type* type = new Type();
    type->setOwnKlass(this);
}

void MethodKlass::print(Object* obj){

}

bool Method::isFunction(Object* obj){
    Klass* klass = obj->klass();
    if((klass != FunctionKlass::getInstance())&&(klass != NativeFunctionKlass::getInstance())){
        return false;
    }
    //Function* func = static_cast<Function*>(obj);
    //return ((func->flags() & Function::CO_GENERATOR) != 0);
    return true;
}

}