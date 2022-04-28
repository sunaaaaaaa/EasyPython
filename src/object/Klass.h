#ifndef __EASY_PYTHON_VM_KLASS_H_
#define __EASY_PYTHON_VM_KLASS_H_
#include <stdio.h>
//表示Class
namespace easy_vm{
//前置声明，因为Object引用了Klass，而Klass又引用了Object    
class Object;
class String;

class Klass{
public:
    Klass(){}
    void setName(String* s){ m_name = s;}
    String* getName(){return m_name;}

    virtual void print(Object* obj1){}
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
private:
    String* m_name;
};

}
#endif