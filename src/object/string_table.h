#ifndef __EASY_PYTHON_VM_STRING_TABLE_H_
#define __EASY_PYTHON_VM_STRING_TABLE_H_
#include "String.h"

namespace easy_vm{
class StringTable{
private:
    static StringTable* instance;
    StringTable();

public:
    static StringTable* getInstance();
    String* m_next;
    String* mod;
    String* init;
    String* add;
    String* call;
    String* getitem;
    String* setitem;
    String* getattr;
    String* setattr;      
};    
}

#endif