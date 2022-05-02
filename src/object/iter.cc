#include "iter.h"
#include "dict.h"
#include "function.h"
namespace easy_vm{
//--------------------------------------列表迭代器-------------------------------------------------------//
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


//----------------------------------------------------------字典迭代器-------------------------------------------------//

DictIterator::DictIterator(Dict* dict):m_dict(dict),m_iter_cnt(0) {}

// template<ITER_TYPE iter_type>
// DictIteratorKlass<iter_type>::DictIteratorKlass() {
//     const char* klass_names[] = {
//         "dictionary-keyiterator",
//         "dictionary-valueiterator",
//         "dictionary-itemiterator",
//     };
//     Dict* dict = new Dict();
//     dict->put(new String("next"),new Function(dict_next));
//     setKlassDict(dict);
//     setName(new String(klass_names[iter_type]));
// }

// template<ITER_TYPE n>
// DictIteratorKlass<n>* DictIteratorKlass<n>::instance = NULL;

// template<ITER_TYPE n>
// DictIteratorKlass<n>* DictIteratorKlass<n>::getInstance(){
//     if(instance == NULL){
//         instance = new DictIteratorKlass<n>();
//     }
//     return instance;
// }

// template<ITER_TYPE iter_type>
// Object* DictIteratorKlass<iter_type>::dict_next(std::vector<Object*>* args){
//     DictIterator* iter = static_cast<DictIterator*>(args->at(0));
    
//     Dict* dict = iter->getDict();
//     int iter_cnt = iter->getIterCnt();

//     if(iter_cnt < dict->getMap()->size()){
//         Object* obj;
//         if(iter_type == ITER_KEY){
//            obj = dict->getMap()->get_key(iter_cnt);
//         }else if(iter_type == ITER_VALUE){
//            obj = dict->getMap()->get_value(iter_cnt);  
//         }else if(iter_type == ITER_ITEM){
//            List* list = new List();
//            list->append(dict->getMap()->get_key(iter_cnt));
//            list->append(dict->getMap()->get_value(iter_cnt)); 
//            obj = list;
//         }
//         iter->incCnt();
//         return obj;
//     }else{
//         return NULL;
//     }
// }

}