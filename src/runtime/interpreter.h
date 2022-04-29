#ifndef __EASY_PYTHON_VM_INTERPRETER_H_
#define __EASY_PYTHON_VM_INTERPRETER_H_
#include "../code/code_object.h"
#include "block.h"
#include "frame.h"
namespace easy_vm{
class Interpreter{
public:
   void run(CodeObject* codes);
   void buildFrame(Object* callable);
   void runMainFrame();
   
   void leaveFrame();
private:
   void destoryFrame();
   Frame*  m_main_frame;
   Object* m_ret_value;
};    
}

#endif