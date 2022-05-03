#include "dict.h"
#include "List.h"
#include "iter.h"
#include "String.h"
#include "function.h"
#include "../runtime/universe.h"
#include <assert.h>
#include <iostream>
namespace easy_vm{

DictKlass* DictKlass::instance = NULL;

DictKlass* DictKlass::getInstance(){
    if(instance == NULL){
        instance = new DictKlass();
        instance->init();
    }
    return instance;
}
//由于Dict和DictKlass互相依赖，因此不能直接在构造函数中创建Dict对象，因此添加init方法
DictKlass::DictKlass(){}

void DictKlass::init(){
    Dict* dict = new Dict();
    dict->put(new String("setdefault"),new Function(Dict::dict_set_default));
    dict->put(new String("remove"),new Function(Dict::dict_delete));
    dict->put(new String("keys"),new Function(Dict::dict_keys));
    dict->put(new String("values"),new Function(Dict::dict_values));
    dict->put(new String("items"),new Function(Dict::dict_items));
    dict->put(new String("iterkeys"),new Function(Dict::dict_iterkeys));
    dict->put(new String("itervalues"),new Function(Dict::dict_itervalues));
    dict->put(new String("iteritems"),new Function(Dict::dict_iteritems));
    setKlassDict(dict);
    Type* type = new Type();
    type->setOwnKlass(this);
    setName(new String("dict"));
    setSuper(ObjectKlass::getInstance());
}

void DictKlass::print(Object* obj){
    Dict* dict = static_cast<Dict*>(obj);
    assert(dict && dict->klass() == static_cast<Klass*>(this));
    std::cout << "{";
    int size = dict->size();
    if(size > 0){
       dict->getMap()->get_key(0)->print();
       std::cout << ":";
       dict->getMap()->get_value(0)->print(); 
    }
    for(int i = 1;i<size;++i){
       std::cout << ",";
       dict->getMap()->get_key(i)->print();
       std::cout << ":";
       dict->getMap()->get_value(i)->print();     
    } 
    std::cout<<"}"<<std::endl;
}

Object* DictKlass::allocateInstance(Object* objType,std::vector<Object*>* args){
    if (!args || args->size() == 0)
        return new Dict();
    else
        return NULL;
}

Object* DictKlass::subscr(Object* obj,Object* index){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    Dict* dict = static_cast<Dict*>(obj);
    return dict->get(index);
}

void DictKlass::storeSubscr(Object* obj,Object* index,Object* value){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    Dict* dict = static_cast<Dict*>(obj);
    dict->put(index,value);
}

void DictKlass::delSubscr(Object* obj,Object* ele){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    Dict* dict = static_cast<Dict*>(obj);
    dict->remove(ele);
}

Object* DictKlass::contains(Object* obj,Object* ele){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    Dict* dict = static_cast<Dict*>(obj);
    if(dict->hasKey(ele)){
        return Universe::True;
    }
    return Universe::False;
}

Object* DictKlass::iter(Object* obj){

} 

Dict::Dict(){
    m_map = new Map<Object*,Object*>();
    //std::cout << "aaa" << std::endl;
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


Object* Dict::dict_set_default(std::vector<Object*>* args){
    assert(args->size() == 3);
    Dict* dict = static_cast<Dict*>(args->at(0));
    Object* key = args->at(1);
    Object* value = args->at(2);
    if(!dict->hasKey(key)){
        dict->put(key,value);
    }
    return Universe::None;
}

Object* Dict::dict_delete(std::vector<Object*>* args){
    assert(args->size() == 2);
    Dict* dict = static_cast<Dict*>(args->at(0));
    Object* key = args->at(1);
    dict->remove(key);
    return Universe::None;
}

Object* Dict::dict_keys(std::vector<Object*>* args){
    Dict* dict = static_cast<Dict*>(args->at(0));
    List* result = new List();
    for(int i = 0;i < dict->size();++i){
        result->append(dict->getMap()->get_key(i));
    }
    return result;
}

Object* Dict::dict_values(std::vector<Object*>* args){
    Dict* dict = static_cast<Dict*>(args->at(0));
    List* result = new List();
    for(int i = 0;i < dict->size();++i){
        result->append(dict->getMap()->get_value(i));
    }
    return result;
} 

Object* Dict::dict_items(std::vector<Object*>* args){
    Dict* dict = static_cast<Dict*>(args->at(0));
    List* result = new List();
    for(int i = 0;i < dict->size();++i){
        List* item = new List();
        item->append(dict->getMap()->get_key(i));
        item->append(dict->getMap()->get_value(i));
        result->append(item);
    }
    return result;
} 

Object* Dict::dict_iterkeys(std::vector<Object*>* args){
    Dict* dict = static_cast<Dict*>(args->at(0));
    Object* it = new DictIterator(dict);
    it->setKlass(DictIteratorKlass<ITER_KEY>::getInstance());
    return it;
}

Object* Dict::dict_itervalues(std::vector<Object*>* args){
    Dict* dict = static_cast<Dict*>(args->at(0));
    Object* it = new DictIterator(dict);
    it->setKlass(DictIteratorKlass<ITER_VALUE>::getInstance());
    return it;
}

Object* Dict::dict_iteritems(std::vector<Object*>* args){
    Dict* dict = static_cast<Dict*>(args->at(0));
    Object* it = new DictIterator(dict);
    it->setKlass(DictIteratorKlass<ITER_ITEM>::getInstance());
    return it;
}

}