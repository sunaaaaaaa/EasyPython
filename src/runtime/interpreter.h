#ifndef __EASY_PYTHON_VM_INTERPRETER_H_
#define __EASY_PYTHON_VM_INTERPRETER_H_
#include "../code/code_object.h"
namespace easy_vm{
class Interpreter{
public:
   void run(CodeObject* codes);
private:
   std::vector<Object*>* m_stack;
   std::vector<Object*>* m_consts;   
};    
}

#endif