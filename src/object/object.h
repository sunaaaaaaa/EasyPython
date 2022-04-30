#ifndef __EASY_PYTHON_VM_OBJECT_H_
#define __EASY_PYTHON_VM_OBJECT_H_
#include "Klass.h"
#include <assert.h>

namespace easy_vm{
class Object{
public:
   Object(){}
   Klass* klass(){
      assert(m_klass!=NULL);
      return m_klass;
   }
   void setKlass(Klass* kls){ m_klass = kls;}
   void print();
   Object* len();
   Object* add(Object* obj);
   Object* sub(Object* obj);
   Object* mul(Object* obj);
   Object* div(Object* obj);
   Object* mod(Object* obj);
   Object* greater(Object* obj);
   Object* less(Object* obj);
   Object* equal(Object* obj);
   Object* not_equal(Object* obj);
   Object* ge(Object* obj);
   Object* le(Object* obj);
   Object* subscr(Object* obj);//取下标操作，用于String类和List类，其他类该方法不实现
   Object* contains(Object* obj);
private:
   Klass* m_klass;   
};
}

#endif