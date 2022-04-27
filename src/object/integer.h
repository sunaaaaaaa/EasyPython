#ifndef __EASY_PYTHON_VM_INTEGER_H_
#define __EASY_PYTHON_VM_INTEGER_H_
#include "object.h"
namespace easy_vm{

class Integer:public Object{
public:
     Integer(int val):m_value(val){}
     int value() const {return m_value;}
     void print();
     Object* add(Object* obj);
     Object* greater(Object* obj);
     Object* less(Object* obj);
     Object* equal(Object* obj);
     Object* not_equal(Object* obj);
     Object* ge(Object* obj);
     Object* le(Object* obj);
private:
     int m_value;
};

}

#endif