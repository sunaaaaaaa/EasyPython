#include "code_object.h"
#include <iostream>
namespace easy_vm{

CodeObject::CodeObject(int argcount, int nlocals, int stacksize, int flag, String* bytecodes,
        std::vector<Object*>* consts, std::vector<Object*>* names, 
        std::vector<Object*>* arglist, 
        std::vector<Object*>* freevars, std::vector<Object*>* cellvars,
        String* file_name, String* co_name, int lineno, String* notable)
        :m_argCount(argcount),m_locals(nlocals),m_stackSize(stacksize),m_flag(flag),m_byteCode(bytecodes)
        ,m_file_name(file_name),m_co_name(co_name),m_lineNum(lineno),m_notable(notable),m_consts(consts)
        ,m_names(names),m_argList(arglist),m_free_vars(freevars),m_cell_vars(cellvars){}


}