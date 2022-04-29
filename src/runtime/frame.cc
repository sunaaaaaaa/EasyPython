#include "frame.h"
#include <iostream>
namespace easy_vm{
//该构造函数仅用于main函数
Frame::Frame(CodeObject* codes):m_consts(codes->m_consts),m_names(codes->m_names),
                                m_codes(codes),m_pc(0),m_arg_list(codes->m_argList),m_sender(NULL){
    m_locals = new Map<Object*,Object*>();
    m_stack = new std::vector<Object*>();
    m_loop_stack = new std::vector<Block*>();
    m_globals = m_locals;
}

Frame::Frame(Function* func):m_consts(func->m_codes->m_consts),m_names(func->m_codes->m_names),m_codes(func->m_codes),m_pc(0){
    m_locals = new Map<Object*,Object*>();
    m_stack = new std::vector<Object*>();
    m_loop_stack = new std::vector<Block*>();
    m_globals = func->getGlobals();
    m_arg_list = NULL;
    m_sender = NULL; 
}

Frame::Frame(Function* func,std::vector<Object*>* args)
      :m_consts(func->m_codes->m_consts),m_names(func->m_codes->m_names),m_codes(func->m_codes),m_pc(0){
    m_locals = new Map<Object*,Object*>();
    m_stack = new std::vector<Object*>();
    m_loop_stack = new std::vector<Block*>();
    m_globals = func->getGlobals();
    m_arg_list = new std::vector<Object*>(m_codes->m_argCount,0);
    m_sender = NULL;

    if(func->m_defaults){
        int def_cnt = func->m_defaults->size();
        int arg_cnt = m_codes->m_argCount;
        while(def_cnt){
            def_cnt--;
            --arg_cnt;
            auto& temp = m_arg_list->at(arg_cnt);
            temp = func->m_defaults->at(def_cnt);
        }
    }
    if(m_arg_list->size()==3){
        m_arg_list->at(1)->print();
        
    }
    if(args){
       for(int i = 0;i<args->size();++i){
           auto& temp = m_arg_list->at(i);
           temp = args->at(i);
       }
    }
}

bool Frame::hasMoreCodes(){
    return m_pc < m_codes->m_byteCode->length();
}

unsigned char Frame::getOpCode(){
   return m_codes->m_byteCode->value()[m_pc++];
}

int Frame::getOpArg(){
   int byte = m_codes->m_byteCode->value()[m_pc++] & 0xff;
   int byte2 = m_codes->m_byteCode->value()[m_pc++] & 0xff;
   return byte2 << 8 | byte; 
}


}