#ifndef __EASY_PYTHON_VM_FRAME_H_
#define __EASY_PYTHON_VM_FRAME_H_
#include <vector>
#include "../code/code_object.h"
#include "../object/object.h"
#include "../util/map.h"
#include "block.h"

//栈帧
namespace easy_vm{
class Frame{
public:
   Frame(CodeObject* codes);
   Frame();
   std::vector<Object*>* m_stack;    //执行栈
   std::vector<Block*>* m_loop_stack;//代码块深度栈
   std::vector<Object*>* m_consts; //常量表引用
   std::vector<Object*>* m_names;  //变量名表引用
   Map<Object*,Object*>* m_locals; //本地变量
   CodeObject* m_codes; //执行代码
   int m_pc;//当前栈帧的pc 
public:
   void setPc(int pc){m_pc = pc;}
   int getPc(){return m_pc;}
   std::vector<Object*>* getStack(){return m_stack;}    
   std::vector<Block*>* getLoopStack(){return m_loop_stack;}
   std::vector<Object*>* mConsts(){return m_consts;} 
   std::vector<Object*>* mNames(){return m_names;}  
   Map<Object*,Object*>* mLocals(){return m_locals;}

   bool hasMoreCodes();
   unsigned char getOpCode();
   int getOpArg(); 
};
}
#endif