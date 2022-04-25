#include "String.h"
#include <string.h>
#include <stdlib.h>
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
}