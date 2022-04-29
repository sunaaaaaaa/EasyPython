#include "frame.h"

namespace easy_vm{
//该构造函数仅用于main函数
Frame::Frame(CodeObject* codes):m_consts(codes->m_consts),m_names(codes->m_names),
                                m_codes(codes),m_pc(0),m_sender(NULL){
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
    m_sender = NULL; 
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