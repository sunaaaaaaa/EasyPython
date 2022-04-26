#include "interpreter.h"
#include "../code/bytecode.hpp"
#include "../object/integer.h"
#include "../object/String.h"
#include <vector>
#include <iostream>
namespace easy_vm{

void Interpreter::run(CodeObject* codes){
    int pc = 0;
    int code_length = codes->m_byteCode->length();

    m_stack = new std::vector<Object*>();
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
                v = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                v->print();
                break;
            case ByteCode::PRINT_NEWLINE:
                std::cout<<std::endl;
                break;
            case ByteCode::BINARY_ADD:
                v = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                w = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                m_stack->push_back(w->add(v));
                break;
            case ByteCode::RETURN_VALUE:
                m_stack->pop_back();
                break;
            default:
                std::cout << "Error:Unrecognized byte code "<<op_code <<std::endl;                 
        }
    }

}

} 
