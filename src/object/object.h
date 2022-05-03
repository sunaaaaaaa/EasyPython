#ifndef __EASY_PYTHON_VM_OBJECT_H_
#define __EASY_PYTHON_VM_OBJECT_H_
#include "Klass.h"
#include <assert.h>

namespace easy_vm{

class ObjectKlass:public Klass{
private:
   ObjectKlass();
   static ObjectKlass* instance;
public:
   static ObjectKlass* getInstance();
   static void init(Klass* kls);   
};

class Object{
public:
   Object(){}
   Klass* klass(){
      assert(m_klass!=NULL);
      return m_klass;
   }
   void setKlass(Klass* kls){ m_klass = kls;}
   void setObjAttr(Dict* dict){m_objAttr = dict;}
   Dict* getObjAttr(){return m_objAttr;}
   void initObjAttr();

   void print();
   Object* getattr(Object* attr);
   Object* setattr(Object* attr,Object* value);
   Object* len();
   Object* add(Object* obj);
   Object* sub(Object* obj);
   Object* mul(Object* obj);
   Object* div(Object* obj);
   Object* mod(Object* obj);
   Object* greater(Object* obj);
   Object* less(Object* obj);
   Object* equal(Object* obj);
   Object* not_equal(Object* obj);
   Object* ge(Object* obj);
   Object* le(Object* obj);
   Object* subscr(Object* index);//取下标操作，用于String类和List类，其他类该方法不实现
   void storeSubscr(Object* index,Object* value);//修改对应下标元素
   void delSubscr(Object* obj);
   Object* contains(Object* obj);
   Object* iter();
private:
   Klass* m_klass;
   Dict* m_objAttr;//存放为该对象添加的属性，即当创建某个自定义类型的对象时，可以动态为该对象添加一些属性而不应该该类型的其他对象   
};

class TypeKlass:public Klass{
private:
   TypeKlass(){}
   static TypeKlass* instance;
public:
   static void init(Klass* kls);
   static TypeKlass* getInstance();
   virtual void print(Object* obj);
};

class Type:public Object{
private:
   Klass* m_own_klass;//Klass的类型对象，由于Klass本身也可以看作一个对象，需要获取一些Klass本身的属性时，需要对外提供接口
                      //而为了不破坏Klass表示类型，Object表示对象的清晰结构，因此在Klass中设置一个Object的子类Type，专门记录Klass的一些属性
                      //对外提供  
public:
   Type();
   void setOwnKlass(Klass* kls);
   Klass* getOwnKlass(){return m_own_klass;};          
};

}

#endif