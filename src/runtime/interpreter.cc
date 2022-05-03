#include <vector>
#include <iostream>
#include <map>
#include "cell.h"
#include "universe.h"
#include "interpreter.h"
#include "../code/bytecode.hpp"
#include "../object/List.h"
#include "../object/integer.h"
#include "../object/String.h"
#include "../object/method.h"
#include "../object/function.h"
#include "../object/string_table.h"
#include "../util/map.h"


#define STACK_LEVEL() m_main_frame->m_stack->size()
#define STACK_TOP() m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1)
namespace easy_vm{

Interpreter::Interpreter(){
    m_builtins = new Map<Object*,Object*>;
    m_builtins->put(new String("True"),Universe::True);
    m_builtins->put(new String("False"),Universe::False);
    m_builtins->put(new String("None"),Universe::None);
    m_builtins->put(new String("len"),new Function(len));
    m_builtins->put(new String("type"),new Function(type));
    m_builtins->put(new String("isinstance"),new Function(isInstance));
    m_builtins->put(new String("int"),IntegerKlass::getInstance()->getType());
    // m_builtins->put(new String("object"),IntegerKlass::getInstance()->getType());
    m_builtins->put(new String("str"),StringKlass::getInstance()->getType());
    m_builtins->put(new String("list"),ListKlass::getInstance()->getType());
    m_builtins->put(new String("dict"),DictKlass::getInstance()->getType());
}

void Interpreter::run(CodeObject* codes){
    m_main_frame = new Frame(codes);
    m_main_frame->m_stack->resize(codes->m_stackSize);
    m_ret_value = NULL;
    runMainFrame();
    destoryFrame();    
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
        std::vector<Object*>* args = NULL; 
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
                //先从本地变量字典中取
                if(w != Universe::None){
                    m_main_frame->m_stack->push_back(w);
                    break;
                }
                //取不到则从全局变量字典中取
                w = m_main_frame->m_globals->get(v);
                if(w != Universe::None){
                    m_main_frame->m_stack->push_back(w);
                    break;
                }
                //寻找内置变量表
                w = m_builtins->get(v);
                if(w != Universe::None){
                    m_main_frame->m_stack->push_back(w);
                    break;
                }
                //如果都找不到，则压入空对象
                m_main_frame->m_stack->push_back(Universe::None);
                break;
            case ByteCode::STORE_NAME:
                //放入变量字典
                v = m_main_frame->m_names->at(op_arg);
                m_main_frame->m_locals->put(v,m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1));
                m_main_frame->m_stack->pop_back(); 
                break; 
            case ByteCode::LOAD_GLOBAL:   
                v = m_main_frame->m_names->at(op_arg);
                w = m_main_frame->m_globals->get(v);
                if(w != Universe::None){
                    m_main_frame->m_stack->push_back(w);
                    break;
                }
                w = m_builtins->get(v);
                if(w != Universe::None){
                    m_main_frame->m_stack->push_back(w);
                    break;
                }
                m_main_frame->m_stack->push_back(Universe::None);
                break;    
            case ByteCode::STORE_GLOBAL:
                 v = m_main_frame->m_names->at(op_arg);
                 m_main_frame->m_globals->put(v,m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1));
                 m_main_frame->m_stack->pop_back();
                 break;
            case ByteCode::LOAD_FAST:
                v = m_main_frame->m_arg_list->at(op_arg);
                m_main_frame->m_stack->push_back(v); 
                break;
            case ByteCode::STORE_FAST:
                v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                m_main_frame->m_stack->pop_back();
                if(op_arg >= m_main_frame->m_arg_list->size()){
                    m_main_frame->m_arg_list->resize(op_arg + 1);
                }
                {
                   auto& temp = m_main_frame->m_arg_list->at(op_arg);
                   temp = v;
                }
                break;
            case ByteCode::LOAD_ATTR:
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                w = m_main_frame->m_names->at(op_arg);
                m_main_frame->m_stack->push_back(v->getattr(w));
                break;
            case ByteCode::STORE_ATTR:
                break;     
            case ByteCode::LOAD_CLOSURE:
                v = m_main_frame->mClosure()->get(op_arg);
                if(v == NULL){
                    v = m_main_frame->getCellFromParamter(op_arg);
                    m_main_frame->mClosure()->set(op_arg,v);
                }
                if(v->klass() == CellKlass::getInstance()){
                    m_main_frame->m_stack->push_back(v);
                }else{
                    m_main_frame->m_stack->push_back(new Cell(m_main_frame->mClosure(),op_arg));
                }
                break;
            case ByteCode::LOAD_DEREF:
                v = m_main_frame->mClosure()->get(op_arg);
                if(v->klass() == CellKlass::getInstance()){
                    v = static_cast<Cell*>(v)->getValue();
                }
                m_main_frame->m_stack->push_back(v);
                break;
            case ByteCode::STORE_DEREF:
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                m_main_frame->mClosure()->set(op_arg,v);
                break;    
            case ByteCode::MAKE_CLOSURE:
                v = STACK_TOP();
                
                m_main_frame->m_stack->pop_back();
                subFunc = new Function(v);
                subFunc->setClosure(static_cast<List*>(STACK_TOP()));
                m_main_frame->m_stack->pop_back();
                subFunc->setGlobals(m_main_frame->mGlobals());
                if(op_arg > 0){
                   args = new std::vector<Object*>();
                   while(op_arg--){
                        v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                        m_main_frame->m_stack->pop_back();
                        args->push_back(v);
                   }
                   
                   subFunc->setDefaults(args);
                }
                if(args != NULL){
                    delete args;
                    args = NULL;
                }
                m_main_frame->m_stack->push_back(subFunc);
                break;
            case ByteCode::LOAD_LOCALS:
                //m_main_frame->m_stack->push_back(m_main_frame->m_locals);
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
            case ByteCode::BINARY_SUBTRACT:
                break;
            case ByteCode::BINARY_MULTIPLY:
                break;
            case ByteCode::BINARY_DIVIDE:
                break;       
            case ByteCode::BINARY_SUBSCR:
                //取列表或字符串元素
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                w = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                m_main_frame->m_stack->push_back(w->subscr(v)); 
                break;
            case ByteCode::BINARY_MODULO:
                break;    
            case ByteCode::STORE_SUBSCR:
                //使用下标修改列表或字符串对应元素
                u = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                w = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                v->storeSubscr(u,w);
                break;
            case ByteCode::DELETE_SUBSCR:
                w = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                v->delSubscr(w);
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
                case ByteCode::IS:
                    if(v == w){
                        m_main_frame->m_stack->push_back(Universe::True);
                    }else{
                        m_main_frame->m_stack->push_back(Universe::False);
                    }
                    break;
                case ByteCode::IS_NOT:
                    if(v == w){
                        m_main_frame->m_stack->push_back(Universe::False);
                    }else{
                        m_main_frame->m_stack->push_back(Universe::True);
                    }
                    break;                     
                case ByteCode::IN:
                    m_main_frame->m_stack->push_back(w->contains(v));
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
            case ByteCode::POP_TOP:
                m_main_frame->m_stack->pop_back();
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
                subFunc->setGlobals(m_main_frame->mGlobals());
                //此处提出的为函数的默认参数
                if(op_arg > 0){
                   args = new std::vector<Object*>();
                   while(op_arg--){
                        v = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                        m_main_frame->m_stack->pop_back();
                        args->push_back(v);
                   }
                   
                   subFunc->setDefaults(args);
                }
                if(args != NULL){
                    delete args;
                    args = NULL;
                }
                m_main_frame->m_stack->push_back(subFunc);
                break;
            case ByteCode::CALL_FUNCTION:
                //此处为函数运行传入的实参
                if(op_arg > 0){
                    int na = op_arg & 0xff;//取低8位
                    int nk = op_arg >> 8;  //高8位
                    int arg_cnt = na + 2*nk; //高8位对应键参数的值，由于每个键参数都对应键和参数两个值，因此需要*2

                    args = new std::vector<Object*>();
                    args->resize(op_arg);
                    while(op_arg--){
                        v = STACK_TOP();
                        m_main_frame->m_stack->pop_back();
                        auto& temp = args->at(op_arg);
                        temp = v;
                    }
                }
                
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                buildFrame(v,args,op_arg);
                if(args != NULL){
                    delete args;
                    args = NULL;
                }
                break;    
            case ByteCode::BUILD_TUPLE:
            case ByteCode::BUILD_LIST:
                v = new List();
                while(op_arg--){
                    w = m_main_frame->m_stack->at(m_main_frame->m_stack->size()-1);
                    m_main_frame->m_stack->pop_back();
                    static_cast<List*>(v)->set(op_arg,w);
                }
                m_main_frame->m_stack->push_back(v);
                break; 
            case ByteCode::BUILD_MAP:
                v = new Dict();
                m_main_frame->m_stack->push_back(v);
                break;
            case ByteCode::STORE_MAP:
                w = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                u = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                v = STACK_TOP();
                {
                    Dict* dict = static_cast<Dict*>(v);
                    dict->put(w,u);
                }
                break;
            case ByteCode::BUILD_CLASS:
                break;    
            case ByteCode::GET_ITER:
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                m_main_frame->m_stack->push_back(v->iter());
                break;
            case ByteCode::FOR_ITER:
                v = STACK_TOP();
                w = v->getattr(StringTable::getInstance()->m_next);
                buildFrame(w,NULL,op_arg);
                if(STACK_TOP() == NULL){
                    m_main_frame->m_pc += op_arg;
                    m_main_frame->m_stack->pop_back();
                }
                break;  
            case ByteCode::UNPACK_SEQUENCE:
                v = STACK_TOP();
                m_main_frame->m_stack->pop_back();
                while(op_arg--){
                    m_main_frame->m_stack->push_back(v->subscr(new Integer(op_arg)));
                }
                break;
            default:
                std::cout << "Error:Unrecognized byte code: "<<std::dec<<(int)op_code <<std::endl;                 
        }
        
    }
}
//创建栈帧
void Interpreter::buildFrame(Object* callable, std::vector<Object*>* argList,int op_arg){ 
    if(callable->klass()==NativeFunctionKlass::getInstance()){  
       //执行内置函数,将结果压栈
       m_main_frame->m_stack->push_back(static_cast<Function*>(callable)->call(argList));
    }else if(callable->klass() == MethodKlass::getInstance()){
       Method* method = static_cast<Method*>(callable);
       if(!argList){
           argList = new std::vector<Object*>();
       }
       argList->insert(argList->begin(),method->getOwner());
       buildFrame(method->getFunc(),argList,op_arg + 1);
    }else if(callable->klass() == FunctionKlass::getInstance()){
       Frame* frame = new Frame(static_cast<Function*>(callable),argList,op_arg);
       frame->setSender(m_main_frame);
       m_main_frame = frame; 
    }else if(callable->klass() == TypeKlass::getInstance()){
        Object* inst = static_cast<Type*>(callable)->getOwnKlass()->allocateInstance(argList);
        m_main_frame->m_stack->push_back(inst);
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
