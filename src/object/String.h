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
   int length()const{return m_length;} 
private:
   char* m_value;
   int   m_length; 
};

}

#endif