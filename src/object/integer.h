#ifndef __EASY_PYTHON_VM_INTEGER_H_
#define __EASY_PYTHON_VM_INTEGER_H_
#include "object.h"
namespace easy_vm{

class IntegerKlass:public Klass{
private:
   IntegerKlass();
   static IntegerKlass* instance;

public:
   static IntegerKlass* getInstance();

   virtual void print(Object* obj);
   virtual Object* add(Object* l,Object* r);
   virtual Object* sub(Object* l,Object* r);
   virtual Object* mul(Object* l,Object* r);
   virtual Object* div(Object* l,Object* r);
   virtual Object* mod(Object* l,Object* r);
   virtual Object* greater(Object* l,Object* r);
   virtual Object* less(Object* l,Object* r);
   virtual Object* equal(Object* l,Object* r);
   virtual Object* not_equal(Object* l,Object* r);
   virtual Object* ge(Object* l,Object* r);
   virtual Object* le(Object* l,Object* r);
};


class Integer:public Object{
public:
     Integer(int val):m_value(val){
          setKlass(IntegerKlass::getInstance());
     }
     int value() const {return m_value;}
private:
     int m_value;
};



}

#endif