#ifndef __EASY_PYTHON_VM_METHOD_H_
#define __EASY_PYTHON_VM_METHOD_H_
#include "Klass.h"
#include "dict.h"
#include "object.h"
#include "function.h"
namespace easy_vm{
//表示一个方法
class MethodKlass:public Klass{
private:
    MethodKlass();
    static MethodKlass* instance;
public:
    static MethodKlass* getInstance();
    virtual void print(Object* obj);
};

class Method:public Object{
friend class MethodKlass;
private:
   Object* m_owner;//方法的调用者
   Function* m_func;
public:
   Method(Function* func):m_owner(NULL),m_func(func){
       setKlass(MethodKlass::getInstance());
   }
   Method(Function* func,Object* owner):m_owner(owner),m_func(func){
       setKlass(MethodKlass::getInstance());
   }

   void setOwner(Object* owner){ m_owner = owner;}
   Object* getOwner(){return m_owner;}
   Function* getFunc(){return m_func;}

   static bool isFunction(Object* obj);   
};

}
#endif