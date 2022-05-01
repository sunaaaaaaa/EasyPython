#include "iter.h"
#include "dict.h"
#include "function.h"
namespace easy_vm{

ListIteratorKlass* ListIteratorKlass::instance = NULL;

ListIteratorKlass* ListIteratorKlass::getInstance(){
    if(instance == NULL){
        instance = new ListIteratorKlass();
    }
    return instance;
}

ListIteratorKlass::ListIteratorKlass(){
    Dict* dict = new Dict();
    dict->put(new String("next"),new Function(ListIterator::listiterator_next));
    setKlassDict(dict);
    setName(new String("listiterator"));
}


ListIterator::ListIterator(List* list):m_owner(list),m_iter_cnt(0){
    setKlass(ListIteratorKlass::getInstance());
}

Object* ListIterator::listiterator_next(std::vector<Object*>* args){
    ListIterator* iter = static_cast<ListIterator*>(args->at(0));
    List* list = iter->getOwner();
    int iter_cnt = iter->m_iter_cnt;
    if(iter_cnt < list->size()){
        Object* t = list->get(iter_cnt);
        iter->incIterCnt();
        return t; 
    }else{
        return NULL;
    }

}

}