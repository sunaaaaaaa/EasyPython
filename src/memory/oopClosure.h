#ifndef __EASY_PYTHON_VM_OOP_CLOSURE_H_
#define __EASY_PYTHON_VM_OOP_CLOSURE_H_
#include "../object/object.h"
#include "../util/array_list.h"
namespace easy_vm{
//垃圾回收算法，引用计数
class OopClosure{
public:
    virtual void do_oop(Object* obj) = 0;
    virtual void do_array_list();
};
}

#endif