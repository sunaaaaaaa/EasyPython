#include "String.h"
#include "../runtime/universe.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
namespace easy_vm{

StringKlass* StringKlass::instance = NULL;

StringKlass* StringKlass::getInstance(){
    if(instance == NULL){
        instance = new StringKlass();
    }
    return instance;
}


String::String(const char* str):m_length(strlen(str)){
    m_value = new char[m_length];
    strcpy(m_value,str);
    setKlass(StringKlass::getInstance());
}
String::String(const char* str,const int length):m_length(length){
    m_value = new char[m_length];
    for(int i = 0;i < length;++i){
        m_value[i] = str[i];
    }
    setKlass(StringKlass::getInstance());
}
String::~String(){
    if(m_value!=nullptr){
        delete[] m_value;
        m_value = nullptr;
    }
}

void StringKlass::print(Object* obj){
   String* s = static_cast<String*>(obj);
    
   assert(s && (s->klass()==static_cast<Klass*>(this)));
   for(int i = 0;i<s->length();++i){
       printf("%c",s->value()[i]);
    }
    std::cout << std::endl; 
}

Object* StringKlass::len(Object* obj){
    return new Integer(static_cast<String*>(obj)->length());
}

Object* StringKlass::equal(Object* l,Object* r){
    if(l->klass() != r->klass()){
        return Universe::False;
    }

    String* sl = static_cast<String*>(l);
    String* sr = static_cast<String*>(r);

    assert(sl && sl->klass() == static_cast<Klass*>(this));
    assert(sr && sr->klass() == static_cast<Klass*>(this));
    
    if(sl->length() != sr->length()){
        return Universe::False;
    }
    for(int i = 0;i<sl->length();++i){
        if(sl->value()[i] != sr->value()[i]){
            return Universe::False;
        }
    }
    return Universe::True;
}
// Object* String::greater(Object* obj){}
// Object* String::less(Object* obj){}

// Object* String::not_equal(Object* obj){}
// Object* String::ge(Object* obj){}
// Object* String::le(Object* obj){}

}