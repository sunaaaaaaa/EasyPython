#ifndef __EASY_PYTHON_VM_KLASS_H_
#define __EASY_PYTHON_VM_KLASS_H_
#include <stdio.h>
#include <vector>
#include <iostream>
//表示Class
namespace easy_vm{
//前置声明，因为Object引用了Klass，而Klass又引用了Object    
class Object;
class String;
class Dict;
class List;
class Type;

class Klass{
public:
    Klass();
    void setName(String* s){ m_name = s;}
    String* getName(){return m_name;}
    void setKlassDict(Dict* dict){m_klass_dict = dict;}
    Dict* getKlassDict(){return m_klass_dict;}
    void setType(Type* type){m_type = type;}
    Type* getType(){return m_type;}
    List* getSuper(){return m_super;}
    void setSuper(List* super){m_super = super;}
    List* getMro(){return m_mro;}
    void addSuper(Klass* super);
    void orderSuper();//深度遍历所有父类
    void* operator new(size_t size);

    virtual Object* getattr(Object* obj,Object* attr);
    virtual Object* setattr(Object* obj,Object* attr,Object* value);
    virtual void print(Object* obj1){std::cout <<"自建类型，由于无法重写Klass的该方法，使用默认，打印地址：" <<obj1 << std::endl;}
    virtual Object* len(Object* obj){}
    virtual Object* greater(Object* obj1,Object* obj2){return 0;}
    virtual Object* less(Object* obj1,Object* obj2){return 0;}
    virtual Object* equal(Object* obj1,Object* obj2){return 0;}
    virtual Object* not_equal(Object* obj1,Object* obj2){return 0;}
    virtual Object* ge(Object* obj1,Object* obj2){return 0;}
    virtual Object* le(Object* obj1,Object* obj2){return 0;}
    virtual Object* add(Object* obj1,Object* obj2);
    virtual Object* sub(Object* obj1,Object* obj2){return 0;}
    virtual Object* mul(Object* obj1,Object* obj2){return 0;}
    virtual Object* div(Object* obj1,Object* obj2){return 0;}
    virtual Object* mod(Object* obj1,Object* obj2){return 0;}
    virtual Object* subscr(Object* obj,Object* index);
    virtual void storeSubscr(Object* obj,Object* index,Object* value);
    virtual void delSubscr(Object* obj,Object* ele);
    virtual Object* contains(Object* obj1,Object* obj2){return 0;}
    virtual Object* iter(Object* obj){};
    virtual Object* allocateInstance(Object* objType,std::vector<Object*>* args);
    virtual Object* findAttr(Object* obj,Object* attr);
public:
    static int compareKlass(Klass* kls1,Klass* kls2);
    //第一个为一个Dict，记录方法和属性
    //第二个参数为一个列表，记录父类
    //第三个为字符串常量，表示类名
    static Object* createKlass(Object* attrs,Object* supers,Object* name);
private:
    Object* findAndCall(Object* obj,std::vector<Object*>* args,Object* funcName);
    Object* findAttrInParent(Object* obj,Object* attr);
private:
    String* m_name;
    Dict* m_klass_dict;//存储当前类型的方法和属性
    Type*  m_type;//存储当前Klass类型信息的对象
    List* m_super;//表示该类型的父类型
    List* m_mro; //父类的深度遍历序列(重复元素只保留最后一个)
};

}
#endif