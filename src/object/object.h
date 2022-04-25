#ifndef __EASY_PYTHON_VM_OBJECT_H_
#define __EASY_PYTHON_VM_OBJECT_H_

namespace easy_vm{
class Object{
public:
   virtual void print(){}
   virtual Object* add(Object* obj){}
};
}

#endif