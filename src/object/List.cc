#include "List.h"
#include "integer.h"
#include "dict.h"
#include "iter.h"
#include "method.h"
#include "function.h"
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

ListKlass::ListKlass(){
    Dict* dict = new Dict();
    dict->put(new String("append"),new Function(List::list_append));
    dict->put(new String("replace"),new Function(List::list_replace));
    dict->put(new String("find"),new Function(List::list_find));
    dict->put(new String("pop"),new Function(List::list_pop));
    dict->put(new String("remove"),new Function(List::list_remove));
    dict->put(new String("reverse"),new Function(List::list_reverse));
    dict->put(new String("sort"),new Function(List::list_sort));
    setName(new String("list"));
    setKlassDict(dict);
    Type* type = new Type();
    type->setOwnKlass(this);
    setSuper(ObjectKlass::getInstance());
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

Object* ListKlass::less(Object* obj1,Object* obj2){
    List* ls = static_cast<List*>(obj1);
    assert(ls && ls->klass() == static_cast<Klass*>(this));

    if(obj1->klass() != obj2->klass()){
        if(Klass::compareKlass(obj1->klass(),obj2->klass()) < 0){
            return Universe::True;
        }else{
            return Universe::False;
        }
    }
    
    List* rs = static_cast<List*>(obj2);
    assert(rs && rs->klass() == static_cast<Klass*>(this));
    int len = ls->size() < rs->size() ? ls->size() : rs->size();
    for(int i = 0;i<len; ++i){
        if(ls->get(i) < rs->get(i)){
            return Universe::True;
        }else if(ls->get(i) > rs->get(i)){
            return Universe::False;   
        }
    }

    if(ls->size() < rs->size()){
        return Universe::True;
    }
    return Universe::False;
}

Object* ListKlass::greater(Object* obj1,Object* obj2){
    return less(obj2,obj1);
}

Object* ListKlass::add(Object* obj1,Object* obj2){
    List* list = static_cast<List*>(obj1);
    assert(list && list->klass() == static_cast<Klass*>(this));
    List* list2 = static_cast<List*>(obj2);
    assert(list2 && list2->klass() == static_cast<Klass*>(this));

    List* result = new List();
    for(int i = 0;i < list->size();++i){
        result->m_inner_list->push_back(list->get(i));
    }
    for(int i = 0; i < list2->size(); ++i){
        result->m_inner_list->push_back(list2->get(i));
    }
    return result;
}

//列表只能与整数相乘
Object* ListKlass::mul(Object* obj1,Object* obj2){
    List* list = static_cast<List*>(obj1);
    assert(list && list->klass() == static_cast<Klass*>(this));
    Integer* n = static_cast<Integer*>(obj1);
    assert(n && n->klass() == IntegerKlass::getInstance());

    List* result = new List();
    for(int j = 0;j < n->value();++j){
        for(int i = 0;i < list->size();++i){
           result->m_inner_list->push_back(list->get(i));
        }
    }
    return result;
}

Object* ListKlass::subscr(Object* obj,Object* index){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    assert(index && index->klass() == static_cast<Klass*>(IntegerKlass::getInstance()));
    List* list = static_cast<List*>(obj);
    Integer* idx = static_cast<Integer*>(index);
    return list->get(idx->value());
}

void ListKlass::storeSubscr(Object* obj,Object* index,Object* value){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    assert(index && index->klass() == IntegerKlass::getInstance());

    List* list = static_cast<List*>(obj);
    Integer* idx = static_cast<Integer*>(index);
    list->set(idx->value(),value);
}

void ListKlass::delSubscr(Object* obj,Object* index){
    assert(obj && obj->klass() == static_cast<Klass*>(this));
    assert(index && index->klass() == IntegerKlass::getInstance());
    List* list = static_cast<List*>(obj);
    Integer* idx = static_cast<Integer*>(index);
    list->m_inner_list->erase(list->m_inner_list->begin() + idx->value());
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

Object* ListKlass::iter(Object* obj){
    assert(obj && obj->klass() == this);
    return new ListIterator(static_cast<List*>(obj));
    
}

List::List(){
   setKlass(ListKlass::getInstance());
   m_inner_list = new std::vector<Object*>();
}

List::List(std::vector<Object*>* objList){
   setKlass(ListKlass::getInstance());
   m_inner_list = objList;
}

Object* List::list_append(std::vector<Object*>* args){
   List* list = static_cast<List*>(args->at(0));
   list->append(args->at(1));
   return Universe::None;
}

Object* List::list_replace(std::vector<Object*>* args){
   assert(args->size() == 3);
   List* list = static_cast<List*>(args->at(0));
   Object* index = args->at(1);
   assert(index && index->klass() == IntegerKlass::getInstance());
   Integer* idx = static_cast<Integer*>(index);
   list->set(idx->value(),args->at(2));
   return Universe::None;
}

Object* List::list_find(std::vector<Object*>* args){
    List* list = static_cast<List*>(args->at(0));
    Object* target = args->at(1);
    assert(list && list->klass() == ListKlass::getInstance());

    for(int i = 0;i<list->m_inner_list->size();++i){
        if(list->get(i)->equal(target) == Universe::True){
            return new Integer(i);
        }
    }
    //todo 应该抛出异常，暂时以NULL替代
    return NULL;
}

Object* List::list_pop(std::vector<Object*>* args){
    List* list = static_cast<List*>(args->at(0));
    assert(list && list->klass() == ListKlass::getInstance());
    return list->pop();
}


Object* List::list_remove(std::vector<Object*>* args){
    List* list = static_cast<List*>(args->at(0));
    Object* target = args->at(1);
    assert(list && list->klass() == ListKlass::getInstance());

    for(int i = 0;i<list->m_inner_list->size();++i){
        if(list->get(i)->equal(target) == Universe::True){
            list->m_inner_list->erase(list->m_inner_list->begin() + i);
        }
    }
    return Universe::None;
}

Object* List::list_reverse(std::vector<Object*>* args){
    List* list = static_cast<List*>(args->at(0));
    assert(list && list->klass() == ListKlass::getInstance());

    int i = 0;
    int j = list->size()-1;
    while(i<j){
        Object* t = list->get(i);
        list->set(i,list->get(j));
        list->set(j,t);
        ++i;
        --j;
    }
    return Universe::None;
}

Object* List::list_sort(std::vector<Object*>* args){
    List* list = static_cast<List*>(args->at(0));
    assert(list && list->klass() == ListKlass::getInstance());

    //冒泡排序，后序可以在util包内实现各种排序，将这里改为调排序算法
    for(int i = 0;i<list->size();++i){
        for(int j = list->size()-1; j > i;--j){
            if(list->get(j)->less(list->get(j-1)) == Universe::True){
                Object* t = list->get(j);
                list->set(j,list->get(j-1));
                list->set(j-1,t);
            }
        }
    }
    return Universe::None;
}


}