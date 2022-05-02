#ifndef __EASY_PYTHON_VM_ITER_H_
#define __EASY_PYTHON_VM_ITER_H_
#include "List.h"
#include "dict.h"
#include "Klass.h"
#include "object.h"
#include "function.h"

namespace easy_vm{
//------------------------------------------------------列表迭代器----------------------------------------------------//
class ListIteratorKlass:public Klass{
private:
   ListIteratorKlass();
   static ListIteratorKlass* instance;
public:
   static ListIteratorKlass* getInstance();

   //virtual Object* iter(Object* obj);
};

class ListIterator:public Object{
private:
    List* m_owner; //迭代器迭代对象
    int m_iter_cnt;//迭代器计数器
public:
    ListIterator(List* list);
    List* getOwner(){return m_owner;}
    int getIterCnt(){return m_iter_cnt;}
    void incIterCnt(){m_iter_cnt++;}
public:
    static Object* listiterator_next(std::vector<Object*>* args);
};


// --------------------------------------------------字典迭代器------------------------------------------------------//
enum ITER_TYPE{
    ITER_KEY = 0,
    ITER_VALUE,
    ITER_ITEM
};

template<ITER_TYPE n>
class DictIteratorKlass:public Klass{
private:
   DictIteratorKlass(){
      const char* klass_names[] = {
        "dictionary-keyiterator",
        "dictionary-valueiterator",
        "dictionary-itemiterator",
      };
      Dict* dict = new Dict();
      dict->put(new String("next"),new Function(dict_next));
      setKlassDict(dict);
      setName(new String(klass_names[n]));
   }
   static DictIteratorKlass* instance;
public:
   static DictIteratorKlass* getInstance(){
      if(instance == NULL){
        instance = new DictIteratorKlass<n>();
      }
      return instance;
   }
   virtual Object* iter(Object* obj){return obj;};
   static Object* dict_next(std::vector<Object*>* args);    
};

template<ITER_TYPE n>
DictIteratorKlass<n>* DictIteratorKlass<n>::instance = NULL;

class DictIterator:public Object{
public:
   DictIterator(Dict* dict);
   Dict* getDict(){return m_dict;}
   int getIterCnt(){return m_iter_cnt;}
   void incCnt(){m_iter_cnt++;}
private:
   Dict* m_dict;
   int m_iter_cnt;
};

template<ITER_TYPE iter_type>
Object* DictIteratorKlass<iter_type>::dict_next(std::vector<Object*>* args){
    DictIterator* iter = static_cast<DictIterator*>(args->at(0));
    
    Dict* dict = iter->getDict();
    int iter_cnt = iter->getIterCnt();

    if(iter_cnt < dict->getMap()->size()){
        Object* obj;
        if(iter_type == ITER_KEY){
           obj = dict->getMap()->get_key(iter_cnt);
        }else if(iter_type == ITER_VALUE){
           obj = dict->getMap()->get_value(iter_cnt);  
        }else if(iter_type == ITER_ITEM){
           List* list = new List();
           list->append(dict->getMap()->get_key(iter_cnt));
           list->append(dict->getMap()->get_value(iter_cnt)); 
           obj = list;
        }
        iter->incCnt();
        return obj;
    }else{
        return NULL;
    }
}

}

#endif