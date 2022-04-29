#ifndef __EASY_PYTHON_VM_FUNCTION_H_
#define __EASY_PYTHON_VM_FUNCTION_H_
#include "Klass.h"
#include "object.h"
#include "../util/map.h"
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

//表示一个函数，保存一些函数的动态信息
class Function:public Object{
friend class FunctionKlass;
friend class Frame;    
public:
    Function(Object* obj);
    Function(Klass* klass);
    String* funcName(){return m_funcName;}
    int flags(){return m_flags;}
    Map<Object*,Object*>* getGlobals(){return m_global;}
    void setGlobals(Map<Object*,Object*>* global){ m_global = global;}
    std::vector<Object*>* getDefaults(){return m_defaults;}
    void setDefaults(std::vector<Object*>* defaults);
private:
    String* m_funcName;
    unsigned int m_flags;
    CodeObject* m_codes;             //函数代码  
    Map<Object*,Object*>* m_global;  //函数所在域的全局变量 
    std::vector<Object*>* m_defaults;//参数默认值
};

}

#endif