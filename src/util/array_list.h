#ifndef __EASY_PYTHON_VM_ARRAY_LIST_H_
#define __EASY_PYTHON_VM_ARRAY_LIST_H_
#include <iostream>
namespace easy_vm{

template<class T>
class ArrayList{
public:
   ArrayList(int n = 8);
   ~ArrayList();
   void add(T t);
   void insert(int index,T val);
   T get(int index);
   void set(int index,T t);
   int size();
   int length();
   T pop();
private:
   void expand();    
private:
   int m_length;
   T* m_array;
   int m_size;
};

}

#endif