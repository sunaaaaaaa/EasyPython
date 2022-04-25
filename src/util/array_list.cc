#include "array_list.h"
#include <stdio.h>

namespace easy_vm{

template<class T>
ArrayList<T>::ArrayList(int n):m_length(n),m_size(0){
    m_array = new T[m_length];    
}

template<class T>
ArrayList<T>::~ArrayList(){
    if(m_array != NULL){
        delete[] m_array;
    }    
}

template<class T>
void ArrayList<T>::add(T t){
    if(m_size >= m_length){
        expand();
    }
    //如果没实现拷贝构造呢？
    m_array[m_size++] = t;
}

template<class T>
void ArrayList<T>::insert(int index,T val){
     add(NULL);
     for(int i = m_size;i > index;--i){
         m_array[i] = m_array[i-1];
     }
}

template<class T>
T ArrayList<T>::get(int index){
    return m_array[index];
}

template<class T>
void ArrayList<T>::set(int index,T t){
    if(m_size <= index){
        m_size = index + 1;
    }

    while(m_size > m_length){
        expand();
    }

    m_array[index] = t;
}

template<class T>
int ArrayList<T>::size(){
    return m_size;
}

template<class T>
int ArrayList<T>::length(){
    return m_length; 
}

template<class T>
T ArrayList<T>::pop(){
    return m_array[--m_size];
}

template<class T>
void ArrayList<T>::expand(){
     T* new_array = new T[m_length << 1];
     for(int i = 0; i <m_length;++i){
         new_array[i] = m_array[i];
     }
     delete[] m_array;
     m_array = new_array;
     m_length << 1;

}   
}