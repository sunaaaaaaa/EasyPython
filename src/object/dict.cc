#include "dict.h"

namespace easy_vm{

DictKlass* DictKlass::instance = NULL;

DictKlass* DictKlass::getInstance(){
    if(instance == NULL){
        instance = new DictKlass();
    }
    return instance;
}

void DictKlass::print(Object* obj){

}

Dict::Dict(){
    m_map = new Map<Object*,Object*>();
    setKlass(DictKlass::getInstance());
}

Dict::Dict(Map<Object*,Object*>* dict){
   m_map = dict;
   setKlass(DictKlass::getInstance());
}

void Dict::update(Dict* dict){
    for(int i = 0;i<dict->size();++i){
        put(dict->m_map->get_key(i),dict->m_map->get_value(i));
    }
}

}