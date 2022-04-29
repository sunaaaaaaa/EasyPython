#ifndef __EASY_PYTHON_VM_CODE_OBJECT_H_
#define __EASY_PYTHON_VM_CODE_OBJECT_H_
#include <vector>
#include "../object/object.h"
#include "../object/String.h"

namespace easy_vm{
class CodeObject:public Object{
public:
   CodeObject(int argcount, int nlocals, int stacksize, int flag, String* bytecodes,
        std::vector<Object*>* consts, std::vector<Object*>* names, 
        std::vector<Object*>* arglist, 
        std::vector<Object*>* freevars, std::vector<Object*>* cellvars,
        String* file_name, String* co_name, int lineno, String* notable);
   void print();
private:
    CodeObject();
public:
   int m_argCount;//参数数量
   int m_locals;//局部变量数目
   int m_stackSize;//栈深度
   int m_flag;//字节码开始标志
   String* m_byteCode;//字节码
   std::vector<Object*>* m_consts;//常量表
   std::vector<Object*>* m_names;//变量表
   std::vector<Object*>* m_argList;//参数列表
   std::vector<Object*>* m_free_vars;//用于构建闭包
   std::vector<Object*>* m_cell_vars;//用于构建闭包

   String* m_file_name;//源文件名称
   String* m_co_name;//模块名
   int m_lineNum;//行号
   String* m_notable;
};

}

#endif