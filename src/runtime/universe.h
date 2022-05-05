#ifndef __EASY_PYTHON_VM_UNIVERSE_H_
#define __EASY_PYTHON_VM_UNIVERSE_H_
#include "../object/integer.h"
#include "Space.h"
//定义运行时使用到的一些唯一对象
namespace easy_vm{
class Universe{
public:
    static Integer* True;
    static Integer* False;
    static Object* None;
    static Heap* heap;
    static std::vector<Klass*>* klasses;
    static void genesis();
    static void destory();
};
}
#endif