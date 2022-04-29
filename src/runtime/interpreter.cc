#include <vector>
#include <iostream>
#include <map>
#include "universe.h"
#include "interpreter.h"
#include "../code/bytecode.hpp"
#include "../object/integer.h"
#include "../object/String.h"
#include "../object/function.h"
#include "../util/map.h"


#define STACK_LEVEL() m_main_frame->m_stack->size()

namespace easy_vm{

void Interpreter::run(CodeObject* codes){
    Universe::genesis();
    m_main_frame = new Frame(codes);
    m_main_frame->m_stack->resize(codes->m_stackSize);
    runMainFrame();
    destoryFrame();
    
}

void Interpreter::buildFrame(Object* callable){
    Frame* frame = new Frame(static_cast<Function*>(callable));
    frame->setSender(m_main_frame);
    m_main_frame = frame;
}

void Interpreter::runMainFrame(){
    
    Block* cur_block = NULL;//当前语句块
    
    while(m_main_frame->hasMoreCodes()){
        unsigned char op_code = m_main_frame->getOpCode();
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

        int op_arg = -1;
        if(has_argument){
            op_arg = m_main_frame->getOpArg();
        }
        
        Function* subFunc; 
        Integer* lhs;
        Integer* rhs;
        Object* v,*w,*u,*attr; 
        switch(op_code){
            case ByteCode::LOAD_CONST:
                m_main_frame->m_stack->push_back(m_main_frame->m_consts->at(op_arg));
                break;
            case ByteCode::LOAD_NAME:
                //从变量字典取变量
                v = m_main_frame->m_names->at(op_arg);
                w = m_main_frame->m_locals->get(v);
                if(w != Universe::None){
                    m_main_frame->m_stack->push_back(w);
                    break;
                }
                m_main_frame->m_stack->push_back(Universe::None);
                break;
            case ByteCode::STORE_NAME:
                //放入变量字典
                v = m_main_frame->m_names->at(op_arg);
                m_main_frame->m_locals->put(v,m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1));
                m_main_frame->m_stack->pop_back(); 
                break; 
            case ByteCode::PRINT_ITEM:
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                v->print();
                break;
            case ByteCode::PRINT_NEWLINE:
                std::cout<<std::endl;
                break;
            case ByteCode::BINARY_ADD:
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                w = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                m_main_frame->m_stack->push_back(w->add(v));
                break;
            case ByteCode::RETURN_VALUE:
                m_ret_value = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                //如果当前栈帧是主函数栈帧，则程序退出
                if(m_main_frame->isMainFrame()){
                    return;
                }
                //否则，退出当前栈帧
                leaveFrame();
                break;
            case ByteCode::COMPARE_OP:
                w = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                //判断具体的比较运算符 
                switch (op_arg)
                {
                case ByteCode::GREATER:
                    m_main_frame->m_stack->push_back(v->greater(w));
                    break;
                case ByteCode::LESS:
                    m_main_frame->m_stack->push_back(v->less(w));
                    break;
                case ByteCode::EQUAL:
                    m_main_frame->m_stack->push_back(v->equal(w));    
                    break;
                case ByteCode::NOT_EQUAL:
                    m_main_frame->m_stack->push_back(v->not_equal(w));
                    break;
                case ByteCode::GREATER_EQUAL:
                    m_main_frame->m_stack->push_back(v->ge(w));
                    break;      
                case ByteCode::LESS_EQUAL: 
                    m_main_frame->m_stack->push_back(v->le(w));
                    break;                  
                default:
                    std::cout << "Error: Unrecognized compare op:"<<op_arg<<std::endl; 
                    break;
                }
                break;
            case ByteCode::POP_JUMP_IF_FALSE:
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                if(((Integer*)v)->value()==0){
                    m_main_frame->m_pc = op_arg;
                }
                break;
            case ByteCode::JUMP_FORWARD:
                m_main_frame->m_pc += op_arg;
                break;
            case ByteCode::JUMP_ABSOLUTE:
                //跳至循环起始位置
                m_main_frame->m_pc = op_arg;
                break;
            case ByteCode::SETUP_LOOP:
                m_main_frame->m_loop_stack->push_back(new Block(op_code,m_main_frame->m_pc + op_arg,STACK_LEVEL())); 
                break;
            case ByteCode::POP_BLOCK:
                //循环正常结束
                cur_block = m_main_frame->m_loop_stack->at(m_main_frame->m_loop_stack->size()-1);
                m_main_frame->m_loop_stack->pop_back(); 
                while(STACK_LEVEL() > cur_block->m_level){
                    m_main_frame->m_stack->pop_back();
                }
                break;
            case ByteCode::BREAK_LOOP:
                //当从一个循环中跳出后，需要将当前执行栈中的局部对象清除，因为语句块已经结束，该语句块中的对象的生命周期结束
                cur_block = m_main_frame->m_loop_stack->at(m_main_frame->m_loop_stack->size()-1);
                m_main_frame->m_loop_stack->pop_back();
                while(STACK_LEVEL() > cur_block->m_level){
                    m_main_frame->m_stack->pop_back();
                }
                m_main_frame->m_pc = cur_block->m_target;//地址跳转
                break;             
            case ByteCode::MAKE_FUNCTION:
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                subFunc = new Function(v);
                m_main_frame->m_stack->push_back(subFunc);
                break;
            case ByteCode::CALL_FUNCTION:
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                buildFrame(v);
                break;    
            default:
                std::cout << "Error:Unrecognized byte code: "<<std::hex<<op_code <<std::endl;                 
        }
        
    }
}

//退出当前栈帧，将返回值压入调用者栈
void Interpreter::leaveFrame(){
    destoryFrame();
    m_main_frame->m_stack->push_back(m_ret_value);
}

//销毁当前函数栈帧，同时将返回上一级栈帧
void Interpreter::destoryFrame(){
    Frame* temp = m_main_frame;
    m_main_frame = m_main_frame->getSender();
    delete temp;
}

} 
