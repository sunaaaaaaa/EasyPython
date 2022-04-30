#ifndef __EASY_PYTHON_VM_FUNCTION_H_
#define __EASY_PYTHON_VM_FUNCTION_H_
#include "Klass.h"
#include "object.h"
#include "../util/map.h"
#include "../code/code_object.h"
namespace easy_vm{

//普通函数的class类
class FunctionKlass :public Klass{
private:
    FunctionKlass(){};
    static FunctionKlass* instance;
public:
    static FunctionKlass* getInstance();
    virtual void print(Object* obj);     
};

//native函数的class类
class NativeFunctionKlass:public Klass{
private:
    NativeFunctionKlass(){}
    static NativeFunctionKlass* instance;
public:
    static NativeFunctionKlass* getInstance();    
};

//声明一个指向native执行逻辑的函数指针NativeFuncPointer
//指向的函数返回值为Objec*,参数为std::vector<Object*>*
typedef Object* (*NativeFuncPointer)(std::vector<Object*>* argList);

//表示一个函数，保存一些函数的动态信息
class Function:public Object{
friend class FunctionKlass;
friend class Frame;    
public:
    enum CO_FLAGS {
        CO_VARARGS = 0x4,
        CO_VARKEYWORDS = 0x8,
        CO_GENERATOR = 0x20,
    };

    Function(Object* obj);
    Function(Klass* klass);
    Function(NativeFuncPointer nativeFunc);//用于创建Native函数
    String* funcName(){return m_funcName;}
    int flags(){return m_flags;}
    Map<Object*,Object*>* getGlobals(){return m_global;}
    void setGlobals(Map<Object*,Object*>* global){ m_global = global;}
    std::vector<Object*>* getDefaults(){return m_defaults;}
    void setDefaults(std::vector<Object*>* defaults);

    Object* call(std::vector<Object*>* args);//当Function表示一个Native函数时，通过call去执行native内置函数的逻辑
private:
    String* m_funcName;
    unsigned int m_flags;
    CodeObject* m_codes;             //函数代码  
    Map<Object*,Object*>* m_global;  //函数所在域的全局变量 
    std::vector<Object*>* m_defaults;//参数默认值
    NativeFuncPointer m_native_func;//当Function表示一个Native函数时，该字段才起作用
};

//内置的native函数
Object* len(std::vector<Object*>* args);
Object* iter(std::vector<Object*>* args);
Object* type_of(std::vector<Object*>* args);
Object* builtin_super(std::vector<Object*>* args);
Object* isInstance(std::vector<Object*>* args);
Object* sysgc(std::vector<Object*>* args);
}

#endif