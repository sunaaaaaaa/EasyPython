#ifndef __EASY_PYTHON_VM_STRING_H_
#define __EASY_PYTHON_VM_STRING_H_
#include "object.h"
#include <vector>
namespace easy_vm{

class StringKlass:public Klass{
private:
   StringKlass(){}
   static StringKlass* instance;
public:
   static StringKlass* getInstance();
   void init();
   virtual Object* getattr(Object* obj,Object* attr);
   virtual Object* setattr(Object* obj,Object* attr,Object* value);
   virtual Object* equal(Object* l,Object* r);
   virtual void print(Object* obj);
   virtual Object* len(Object* obj);
   virtual Object* subscr(Object* obj,Object* index);
   virtual Object* contains(Object* obj,Object* ele);
};

class String:public Object{
public:
   String(const char* str);
   String(const char* str,const int length);
   ~String(); 
   const char* value()const{return m_value;}
   int length()const{return m_length;} 
private:
   char* m_value;
   int   m_length; 
};


Object* string_upper(std::vector<Object*>* args);
Object* sting_join(std::vector<Object*>* args);
}

#endif