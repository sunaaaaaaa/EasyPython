#include "string_table.h"

namespace easy_vm{

StringTable* StringTable::instance = NULL;

StringTable* StringTable::getInstance(){
    if(instance == NULL){
        instance = new StringTable();
    }
    return instance;
}

StringTable::StringTable(){
    m_next = new String("next");
    mod = new String("__module__");
    init = new String("__init__");
    add = new String("__add__");
    call = new String("__call__");
    getitem = new String("__getitem__");
    setitem = new String("__setitem__");
    getattr = new String("__getattr__");
    setattr = new String("__setattr__");
}

}