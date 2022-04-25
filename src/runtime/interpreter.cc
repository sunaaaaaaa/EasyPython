#include "interpreter.h"
#include "../code/bytecode.hpp"
#include "../object/integer.h"
#include "../object/String.h"
#include <vector>
namespace easy_vm{

void Interpreter::run(CodeObject* codes){
    int pc = 0;
    int code_length = codes->m_byteCode->length();

    m_stack = new std::vector<Object*>(codes->m_stackSize);
    m_consts = codes->m_consts;

    while(pc < code_length){
        unsigned char op_code = codes->m_byteCode->value()[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

        int op_arg = -1;
        if(has_argument){
            int byte1 = (codes->m_byteCode->value()[pc++] & 0xFF);
            op_arg = ((codes->m_byteCode->value()[pc++] & 0xFF) <<8)|byte1;
        }

        Integer* lhs;
        Integer* rhs;
        Object* v,*w,*u,*attr;

        switch(op_code){
            case ByteCode::LOAD_CONST:
                m_stack->push_back(m_consts->at(op_arg));
                break;
            case ByteCode::PRINT_ITEM:
                //v = m_stack->end();
                v->print();
                break;    
        }
    }

}

} 
