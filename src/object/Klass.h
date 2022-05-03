#ifndef __EASY_PYTHON_VM_KLASS_H_
#define __EASY_PYTHON_VM_KLASS_H_
#include <stdio.h>
#include <vector>
//表示Class
namespace easy_vm{
//前置声明，因为Object引用了Klass，而Klass又引用了Object    
class Object;
class String;
class Dict;
class Type;

class Klass{
public:
    Klass(){}
    void setName(String* s){ m_name = s;}
    String* getName(){return m_name;}
    void setKlassDict(Dict* dict){m_klass_dict = dict;}
    Dict* getKlassDict(){return m_klass_dict;}
    void setType(Type* type){m_type = type;}
    Type* getType(){return m_type;}
    Klass* getSuper(){return m_super;}
    void setSuper(Klass* super){m_super = super;}

    virtual Object* getattr(Object* obj,Object* attr);
    virtual Object* setattr(Object* obj,Object* attr,Object* value);
    virtual void print(Object* obj1){}
    virtual Object* len(Object* obj){}
    virtual Object* greater(Object* obj1,Object* obj2){return 0;}
    virtual Object* less(Object* obj1,Object* obj2){return 0;}
    virtual Object* equal(Object* obj1,Object* obj2){return 0;}
    virtual Object* not_equal(Object* obj1,Object* obj2){return 0;}
    virtual Object* ge(Object* obj1,Object* obj2){return 0;}
    virtual Object* le(Object* obj1,Object* obj2){return 0;}
    virtual Object* add(Object* obj1,Object* obj2){return 0;}
    virtual Object* sub(Object* obj1,Object* obj2){return 0;}
    virtual Object* mul(Object* obj1,Object* obj2){return 0;}
    virtual Object* div(Object* obj1,Object* obj2){return 0;}
    virtual Object* mod(Object* obj1,Object* obj2){return 0;}
    virtual Object* subscr(Object* obj,Object* index){}
    virtual void storeSubscr(Object* obj,Object* index,Object* value){}
    virtual void delSubscr(Object* obj,Object* ele){}
    virtual Object* contains(Object* obj1,Object* obj2){return 0;}
    virtual Object* iter(Object* obj){};
    virtual Object* allocateInstance(std::vector<Object*>* args){return 0;}
public:
    static int compareKlass(Klass* kls1,Klass* kls2);
private:
    String* m_name;
    Dict* m_klass_dict;
    Klass* m_super;//表示该类型的父类型
    Type*  m_type;//存储当前Klass类型信息的对象
};

}
#endif