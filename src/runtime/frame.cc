#include "dict.h"
#include "List.h"
#include "frame.h"
#include <vector>
#include <assert.h>
#include <iostream>
namespace easy_vm{
//该构造函数仅用于main函数
Frame::Frame(CodeObject* codes):m_consts(codes->m_consts),m_names(codes->m_names),
                                m_codes(codes),m_pc(0),m_arg_list(codes->m_argList),m_sender(NULL){
    m_locals = new Dict();
    m_stack = new std::vector<Object*>();
    m_loop_stack = new std::vector<Block*>();
    m_globals = m_locals;
    m_locals->put(new String("__name__"),new String("__main__"));
}

Frame::Frame(Function* func):m_consts(func->m_codes->m_consts),m_names(func->m_codes->m_names),m_codes(func->m_codes),m_pc(0){
    m_locals = new Dict();
    m_stack = new std::vector<Object*>();
    m_loop_stack = new std::vector<Block*>();
    m_globals = func->getGlobals();
    m_arg_list = NULL;
    m_sender = NULL; 
}

Frame::Frame(Function* func,std::vector<Object*>* args,int op_arg)
      :m_consts(func->m_codes->m_consts),m_names(func->m_codes->m_names),m_codes(func->m_codes),m_pc(0){
    
    assert((args && op_arg != 0) || (args == NULL && op_arg == 0));
    m_locals = new Dict();
    m_stack = new std::vector<Object*>();
    m_loop_stack = new std::vector<Block*>();
    m_globals = func->getGlobals();
    m_arg_list = new std::vector<Object*>(m_codes->m_argCount,0);
    m_sender = NULL;
    m_closure = NULL;

    const int argcnt = m_codes->m_argCount; //形参个数
    const int na = op_arg & 0xff; //实参中的位置参数个数
    const int nk = op_arg >> 8; //实参中的键参数的个数
    int kw_pos = argcnt;
    //默认参数,从后向前赋值，因为默认参数之后的参数必须全部拥有默认参数，但前面的可以没有
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
    //实际参数
    if(args){
       for(int i = 0;i<args->size();++i){
           auto& temp = m_arg_list->at(i);
           temp = args->at(i);
       }
    }
    //处理闭包
    std::vector<Object*>* cells = m_codes->m_cell_vars;
    if(cells && cells->size() > 0){
        m_closure = new List();
        for(int i = 0;i< cells->size();++i){
            m_closure->append(NULL);
        }
    }
    if(func->getClosure() && func->getClosure()->size()>0){
        if(m_closure == NULL){
            m_closure = func->getClosure();
        }else{
            m_closure->add(func->getClosure());
        }
    }
    // List* list = NULL;
    // Dict* dict = NULL;
    // //如果形参个数小于实参的个数,则多余的放入一个列表list中存储 
    // if(argcnt < na){
    //    int i = 0;
    //    for(;i< argcnt;++i){
    //        auto& temp = m_arg_list->at(i);
    //        temp = args->at(i);
    //    }
    //    //剩余的位置参数
    //    list = new List();
    //    for(;i<na;++i){
    //        list->append(args->at(i));
    //    }   
    // }else{
    //     //如果实参个数不足或者等于形参
    //     for(int i = 0;i<na;++i){
    //        auto& temp = m_arg_list->at(i);
    //        temp = args->at(i);
    //     }
    // }

    // //处理键参数
    // for(int i = 0;i<nk;++i){
    //    Object* key = args->at(na + 2*i);
    //    Object* value = args->at(na + i*2 + 1);

    //    int index = -1;
    //    //寻找key所表示的形参
    //    for(int j = 0;j<m_codes->m_argList->size();++j){
    //        if(m_codes->m_argList->at(j)->equal(key)){
    //            index = j;
    //            break;
    //        }
    //    }
    //    if(index >= 0){
    //       auto& temp = m_arg_list->at(index);
    //       temp = value; 
    //    }else{
    //        if(dict == NULL){
    //            dict = new Dict();
    //        }
    //    }

    // }

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

Object* Frame::getCellFromParamter(int index){
    Object* cellObj = m_codes->m_cell_vars->at(index);
    
    for(int i = 0;i<m_codes->m_argList->size();++i){
        if(m_codes->m_argList->at(i)->equal(cellObj)){
            index = i;
        }
    }
    return m_arg_list->at(index);
} 

}