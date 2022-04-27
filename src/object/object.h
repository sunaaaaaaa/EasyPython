#ifndef __EASY_PYTHON_VM_OBJECT_H_
#define __EASY_PYTHON_VM_OBJECT_H_

namespace easy_vm{
class Object{
public:
   virtual void print(){}
   virtual Object* add(Object* obj){}
   virtual Object* greater(Object* obj){};
   virtual Object* less(Object* obj){};
   virtual Object* equal(Object* obj){};
   virtual Object* not_equal(Object* obj){};
   virtual Object* ge(Object* obj){};
   virtual Object* le(Object* obj){};
};
}

#endif