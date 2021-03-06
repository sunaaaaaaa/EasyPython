#ifndef __EASY_PYTHON_VM_INTERPRETER_H_
#define __EASY_PYTHON_VM_INTERPRETER_H_
#include "../code/code_object.h"
#include "block.h"
#include "frame.h"
namespace easy_vm{
//解释器
class Interpreter{
public:
   
   void run(CodeObject* codes);
   void buildFrame(Object* callable,std::vector<Object*>* argList,int op_arg);
   void runMainFrame();
   void leaveFrame();
   void enterFrame(Frame* frame);//开始执行python栈帧
   Object* callVitrual(Object* func,std::vector<Object*>* args);
   static Interpreter* getInstance();   
private:
   Interpreter();
   static Interpreter* instance;
private:
   void destoryFrame();
   Frame*  m_main_frame;
   Object* m_ret_value;
   Map<Object*,Object*>* m_builtins;//VM 内置变量
};    
}

#endif