#include "List.h"
#include "integer.h"
#include "../runtime/universe.h"
#include <assert.h>
#include <iostream>
namespace easy_vm{

ListKlass* ListKlass::instance = NULL;

ListKlass* ListKlass::getInstance(){
    if(instance == NULL){
        instance = new ListKlass();
    }
    return instance;
}

void ListKlass::print(Object* obj){
    List* l = static_cast<List*>(obj);
    assert(l && l->klass() == static_cast<Klass*>(this));
    std::cout << "[";
    int size = l->m_inner_list->size();

    if(size >= 1){
        l->m_inner_list->at(0)->print();
    }

    for(int i = 1;i < size; ++i){
       std::cout << ",";
       l->get(i)->print(); 
    }
    std::cout <<"]"<<std::endl;
}

Object* ListKlass::subscr(Object* obj,Object* index){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    assert(index && index->klass() == static_cast<Klass*>(IntegerKlass::getInstance()));
    List* list = static_cast<List*>(obj);
    Integer* idx = static_cast<Integer*>(index);
    return list->get(idx->value());
}

Object* ListKlass::contains(Object* obj,Object* ele){
    List* list = static_cast<List*>(obj);
    assert(list && list->klass() == static_cast<Klass*>(this));
    int size = list->m_inner_list->size();
    for(int i = 0; i<size; ++i){
        if(list->m_inner_list->at(i)->equal(ele)){
            return Universe::True;
        }
    }
    return Universe::False;
}

List::List(){
   setKlass(ListKlass::getInstance());
   m_inner_list = new std::vector<Object*>();
}

List::List(std::vector<Object*>* objList){
   setKlass(ListKlass::getInstance());
   m_inner_list = objList;
}
}