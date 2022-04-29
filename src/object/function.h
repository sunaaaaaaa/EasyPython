#ifndef __EASY_PYTHON_VM_FUNCTION_H_
#define __EASY_PYTHON_VM_FUNCTION_H_
#include "Klass.h"
#include "object.h"
#include "../code/code_object.h"
namespace easy_vm{

class FunctionKlass :public Klass{
private:
    FunctionKlass(){};
    static FunctionKlass* instance;
public:
    static FunctionKlass* getInstance();
    virtual void print(Object* obj);     
};

class Function:public Object{
friend class FunctionKlass;
friend class Frame;    
public:
    Function(Object* obj);
    Function(Klass* klass);
    String* funcName(){return m_funcName;}
    int flags(){return m_flags;}
private:
    String* m_funcName;
    unsigned int m_flags;
    CodeObject* m_codes;
};

}

#endif