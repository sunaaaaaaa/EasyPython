#ifndef __EASY_PYTHON_VM_INTERPRETER_H_
#define __EASY_PYTHON_VM_INTERPRETER_H_
#include "../code/code_object.h"
#include "block.h"
#include "frame.h"
namespace easy_vm{
class Interpreter{
public:
   void run(CodeObject* codes);
   void run2(CodeObject* codes);
private:
   std::vector<Object*>* m_stack;
   std::vector<Object*>* m_consts;
   std::vector<Object*>* m_names;
   std::vector<Block*>* m_loop_stack;//嵌套栈，存储语句块的层次，例如嵌套循环
   Frame*  m_main_frame;
};    
}

#endif