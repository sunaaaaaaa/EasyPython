#ifndef __EASY_PYTHON_VM_STRING_H_
#define __EASY_PYTHON_VM_STRING_H_
#include "object.h"
namespace easy_vm{
class String : public Object{
public:
   String(const char* str);
   String(const char* str,const int length);
   ~String();
   void print();
   const char* value()const{return m_value;}
   virtual Object* greater(Object* obj);
   virtual Object* less(Object* obj);
   virtual Object* equal(Object* obj);
   virtual Object* not_equal(Object* obj);
   virtual Object* ge(Object* obj);
   virtual Object* le(Object* obj);
   int length()const{return m_length;} 
private:
   char* m_value;
   int   m_length; 
};

}

#endif