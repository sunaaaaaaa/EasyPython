#ifndef __EASY_PYTHON_VM_ITER_H_
#define __EASY_PYTHON_VM_ITER_H_
#include "List.h"
#include "Klass.h"
#include "object.h"

namespace easy_vm{

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
}

#endif