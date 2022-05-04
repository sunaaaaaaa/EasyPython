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
}

}