#ifndef __EASY_PYTHON_VM_LIST_H_
#define __EASY_PYTHON_VM_LIST_H_
#include "Klass.h"
#include "object.h"
#include <vector>

namespace easy_vm{

class ListKlass :public Klass{
private:
   ListKlass();
   static ListKlass* instance;
public:
   static ListKlass* getInstance();

   virtual void print(Object* obj);
   virtual Object* subscr(Object* obj,Object* index);
   virtual void storeSubscr(Object* obj,Object* index,Object* value);
   virtual void delSubscr(Object* obj,Object* ele);
   virtual Object* contains(Object* obj,Object* ele);
   virtual Object* less(Object* obj1,Object* obj2);
   virtual Object* greater(Object* obj1,Object* obj2);
   virtual Object* add(Object* obj1,Object* obj2);//列表加法
   virtual Object* mul(Object* obj1,Object* obj2);//列表乘法
   virtual Object* iter(Object* obj);   
};

class List:public Object{
friend class ListKlass;
public:
    List();
    List(std::vector<Object*>* objList);
    
    int size()const{return m_inner_list->size();}
    std::vector<Object*>* getList()const{return m_inner_list;}
    void append(Object* obj){m_inner_list->push_back(obj);}
    Object* pop(){
        if(m_inner_list->size() > 0){
           Object* temp = m_inner_list->at(m_inner_list->size()-1);
           m_inner_list->pop_back();
           return temp; 
        }  
    }
    Object* get(int index){
        assert(index < size());
        return m_inner_list->at(index);
    }
    void set(int index,Object* obj){
        if(index >= m_inner_list->size()){
            m_inner_list->resize(index + 1);
        }
        auto& temp = m_inner_list->at(index);
        temp = obj;
    }
    Object* top(){return get(size()-1);}
    
public:
    static Object* list_append(std::vector<Object*>* args);
    static Object* list_replace(std::vector<Object*>* args);
    static Object* list_find(std::vector<Object*>* args);
    static Object* list_pop(std::vector<Object*>* args);
    static Object* list_remove(std::vector<Object*>* args);
    static Object* list_reverse(std::vector<Object*>* args);
    static Object* list_sort(std::vector<Object*>* args);
private:
    std::vector<Object*>* m_inner_list;   
};



}
#endif