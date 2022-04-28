#include "String.h"
#include "../runtime/universe.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
namespace easy_vm{

String::String(const char* str):m_length(strlen(str)){
    m_value = new char[m_length];
    strcpy(m_value,str);
}
String::String(const char* str,const int length):m_length(length){
    m_value = new char[m_length];
    for(int i = 0;i < length;++i){
        m_value[i] = str[i];
    }
}
String::~String(){
    if(m_value!=nullptr){
        delete[] m_value;
        m_value = nullptr;
    }
}

void String::print(){
    std::cout << m_value <<std::endl;
}

Object* String::greater(Object* obj){}
Object* String::less(Object* obj){}
Object* String::equal(Object* obj){
    if(this == obj){
        return Universe::True;
    }else{
        return Universe::False;
    }
}
Object* String::not_equal(Object* obj){}
Object* String::ge(Object* obj){}
Object* String::le(Object* obj){}

}