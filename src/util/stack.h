#ifndef __EASY_PYTHON_VM_STACK_H_
#define __EASY_PYTHON_VM_STACK_H_

namespace easy_vm{
template<class V>
class Stack{
public:
   Stack(int n = 16){
       m_len = n;
       vector = new V[n];
       m_size = 0;
   }
   
   ~Stack(){
       delete[] vector;
       m_len = 0;
       m_size = 0;
   }
   void push(V v){
       vector[m_size++] = v;
   }
   V pop(){
       return vector[--m_size];
   }
   V top(){
       return vector[m_size - 1];
   }

   int len(){
       return m_len;
   }

   int size(){
       return m_size;
   }

   bool empty(){
       return m_size == 0;
   }
private:
   V* vector;
   int m_len;
   int m_size;
};

}

#endif