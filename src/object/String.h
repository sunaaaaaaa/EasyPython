#ifndef __EASY_PYTHON_VM_STRING_H_
#define __EASY_PYTHON_VM_STRING_H_
#include "object.h"
namespace easy_vm{

class StringKlass:public Klass{
private:
   StringKlass(){}
   static StringKlass* instance;
public:
   static StringKlass* getInstance();
   virtual Object* equal(Object* l,Object* r);
   virtual void print(Object* obj);
   virtual Object* len(Object* obj);
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

}

#endif