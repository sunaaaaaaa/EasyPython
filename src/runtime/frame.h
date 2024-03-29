#ifndef __EASY_PYTHON_VM_FRAME_H_
#define __EASY_PYTHON_VM_FRAME_H_
#include <vector>
#include "block.h"
#include "../util/map.h"
#include "../code/code_object.h"
#include "../object/dict.h"
#include "../object/List.h"
#include "../object/object.h"
#include "../object/function.h"

//栈帧
namespace easy_vm{
class Frame{
public:
   Frame();
   Frame(CodeObject* codes);
   Frame(Function* func); //创建func对应的栈帧
   Frame(Function* func,std::vector<Object*>* objList,int op_arg);
   std::vector<Object*>* m_stack;    //执行栈
   std::vector<Block*>* m_loop_stack;//代码块深度栈
   std::vector<Object*>* m_consts; //常量表引用
   std::vector<Object*>* m_names;  //变量名表引用
   Dict* m_locals; //本地变量
   Dict* m_globals;//全局变量表 
   std::vector<Object*>* m_arg_list;//参数列表
   List* m_closure;//闭包变量
   CodeObject* m_codes; //执行代码
   Frame* m_sender;//调用该函数的函数的栈帧
   int m_pc;//当前栈帧的pc
   bool m_entryFlag; //标记当前栈帧是否是第一个Python代码栈帧，因为虚拟机在执行__init__函数时执行的是python代码(因为该函数不产生字节码) 
public:
   void setPc(int pc){m_pc = pc;}
   int getPc(){return m_pc;}
   void setSender(Frame* frame){m_sender = frame;}
   void setClosure(List* list){m_closure = list;}
   Frame* getSender(){return m_sender;}
   std::vector<Object*>* getStack(){return m_stack;}    
   std::vector<Block*>* getLoopStack(){return m_loop_stack;}
   std::vector<Object*>* mConsts(){return m_consts;} 
   std::vector<Object*>* mNames(){return m_names;}  
   Dict* mLocals(){return m_locals;}
   Dict* mGlobals(){return m_globals;}
   List* mClosure(){return m_closure;}
   bool getEntryFlag(){return m_entryFlag;}
   void setEntryFlag(bool flag){m_entryFlag = flag;}

   bool isMainFrame(){return m_sender == NULL;}
   bool hasMoreCodes();
   unsigned char getOpCode();//获取当前字节码
   int getOpArg();//获取字节码参数的数目
   Object* getCellFromParamter(int index); 
};
}
#endif