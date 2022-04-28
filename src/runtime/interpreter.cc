#include "universe.h"
#include "interpreter.h"
#include "../code/bytecode.hpp"
#include "../object/integer.h"
#include "../object/String.h"
#include "../util/map.h"
#include <vector>
#include <iostream>
#include <map>

#define STACK_LEVEL() m_stack->size()

namespace easy_vm{

void Interpreter::run(CodeObject* codes){
    Universe::genesis();
    int pc = 0;
    int code_length = codes->m_byteCode->length();
    
    m_stack = new std::vector<Object*>();
    m_stack->resize(codes->m_stackSize);
    m_loop_stack = new std::vector<Block*>();
    Block* cur_block = NULL;//当前语句块
    //变量表与常量表
    m_names = codes->m_names;
    m_consts = codes->m_consts;
    //变量字典，k为names中的变量名，v为当前变量的值，注意会内存泄漏，因为每次生成一个新的对象取代原先的对象，但并没有释放原对象的空间
    Map<Object*,Object*> nameMap;
  
    while(pc < code_length){ 
        unsigned char op_code = codes->m_byteCode->value()[pc++];
        //如果操作码大于90，则表示有参数
        //与0xff进行&运算是为了扩成32位的int型
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
            case ByteCode::LOAD_NAME:
                //从变量字典取变量
                v = m_names->at(op_arg);
                w = nameMap.get(v);
                if(w != Universe::None){
                    m_stack->push_back(w);
                    break;
                }
                m_stack->push_back(Universe::None);
                break;
            case ByteCode::STORE_NAME:
                //放入变量字典
                v = m_names->at(op_arg);
                nameMap.put(v,m_stack->at(m_stack->size()-1));
                m_stack->pop_back(); 
                break; 
            case ByteCode::PRINT_ITEM:
                v = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                v->print();
                break;
            case ByteCode::PRINT_NEWLINE:
                //std::cout<<std::endl;
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
            case ByteCode::COMPARE_OP:
                w = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                v = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                //判断具体的比较运算符 
                switch (op_arg)
                {
                case ByteCode::GREATER:
                    m_stack->push_back(v->greater(w));
                    break;
                case ByteCode::LESS:
                    m_stack->push_back(v->less(w));
                    break;
                case ByteCode::EQUAL:
                    m_stack->push_back(v->equal(w));    
                    break;
                case ByteCode::NOT_EQUAL:
                    m_stack->push_back(v->not_equal(w));
                    break;
                case ByteCode::GREATER_EQUAL:
                    m_stack->push_back(v->ge(w));
                    break;      
                case ByteCode::LESS_EQUAL: 
                    m_stack->push_back(v->le(w));
                    break;                  
                default:
                    std::cout << "Error: Unrecognized compare op:"<<op_arg<<std::endl; 
                    break;
                }
                break;
            case ByteCode::POP_JUMP_IF_FALSE:
                v = m_stack->at(m_stack->size()-1);
                m_stack->pop_back();
                if(((Integer*)v)->value()==0){
                    pc = op_arg;
                }
                break;
            case ByteCode::JUMP_FORWARD:
                pc += op_arg;
                break;
            case ByteCode::JUMP_ABSOLUTE:
                //跳至循环起始位置
                pc = op_arg;
                break;
            case ByteCode::SETUP_LOOP:
                m_loop_stack->push_back(new Block(op_code,pc+op_arg,STACK_LEVEL())); 
                break;
            case ByteCode::POP_BLOCK:
                //循环正常结束
                cur_block = m_loop_stack->at(m_loop_stack->size()-1);
                m_loop_stack->pop_back(); 
                while(STACK_LEVEL() > cur_block->m_level){
                    m_stack->pop_back();
                }
                break;
            case ByteCode::BREAK_LOOP:
                //当从一个循环中跳出后，需要将当前执行栈中的局部对象清除，因为语句块已经结束，该语句块中的对象的生命周期结束
                cur_block = m_loop_stack->at(m_loop_stack->size()-1);
                m_loop_stack->pop_back();
                while(STACK_LEVEL() > cur_block->m_level){
                    m_stack->pop_back();
                }
                pc = cur_block->m_target;//地址跳转
                break;             
            default:
                std::cout << "Error:Unrecognized byte code: "<<std::hex<<op_code <<std::endl;                 
        }
    }

}

} 
