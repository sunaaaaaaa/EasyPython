#include "binary_parser.h"
#include <iostream>
#include <assert.h>
#include "../object/integer.h"
namespace easy_vm{

BinaryParser::BinaryParser(BufferedInputStream* stream):m_bufferIns(stream){}

BinaryParser::~BinaryParser(){}

CodeObject* BinaryParser::parse(){
    //读取魔数
    int magic_number = m_bufferIns->read_int();
    std::cout << "magic number is: " <<std::hex << magic_number << std::endl;

    int moddate = m_bufferIns->read_int();//读取修改日期
    std::cout << "modify date is: " <<std::hex << moddate << std::endl;

    char object_type = m_bufferIns->read();
    if(object_type == 'c'){
       CodeObject* result = getCodeObject();
       std::cout << "parser success!" <<std::endl;
       return result; 
    }
    return NULL; 
}

void BinaryParser::initCodeObject(){
    // m_codeObject->m_argCount = m_bufferIns->read_int();
    // std::cout << "arg count: " << m_codeObject->m_argCount <<std::endl;
    // m_codeObject->m_locals = m_bufferIns->read_int();
    // m_codeObject->m_stackSize = m_bufferIns->read_int();
    // m_codeObject->m_flag = m_bufferIns->read_int();
    // m_codeObject->m_byteCode = getByteCode();
    // m_codeObject->m_consts = getConsts();
    // m_codeObject->m_names = getNames();
    // m_codeObject->m_argList = getArgList();
    // m_codeObject->m_free_vars = getFreeVars();
    // m_codeObject->m_cell_vars = getCellVars();
    // m_codeObject->m_file_name = getFileName();
    // m_codeObject->m_co_name = getModuleName();
    // m_codeObject->m_lineNum = m_bufferIns->read_int();
    // m_codeObject->m_notable = getNoTable();
}

CodeObject* BinaryParser::getCodeObject(){
    int argcount  = m_bufferIns->read_int();
    int nlocals   = m_bufferIns->read_int();
    int stacksize = m_bufferIns->read_int();
    int flags     = m_bufferIns->read_int();
     std::cout << "arg count: " << argcount <<std::endl;

    String* byte_codes = getByteCode();
    std::vector<Object*>* consts     = getConsts();
    std::vector<Object*>* names      = getNames();
    std::vector<Object*>* var_names  = getArgList();
    std::vector<Object*>* free_vars  = getFreeVars();
    std::vector<Object*>* cell_vars  = getCellVars();

    String* file_name   = getFileName();
    String* module_name = getModuleName();
    int begin_line_no     = m_bufferIns->read_int();
    String* lnotab      = getNoTable();
    return new CodeObject(argcount, nlocals, stacksize, flags, byte_codes,
        consts, names, var_names, free_vars, cell_vars, file_name, module_name,
        begin_line_no, lnotab);
}

//读取字节码
String* BinaryParser::getByteCode(){
   char ch = m_bufferIns->read();
   assert(ch == 's');
   return  getString();
}

String* BinaryParser::getString(){
   int length = m_bufferIns->read_int();

   char* temp = new char[length];

   for(int i = 0;i<length;i++){
       temp[i] = m_bufferIns->read();
   }
   String* s = new String(temp,length);
   delete[] temp;
   return s;
}
//读取常量表
std::vector<Object*>* BinaryParser::getConsts(){
   if(m_bufferIns->read() == '('){
       return get_tuple();
   }
   m_bufferIns->back();
   return NULL;
}

std::vector<Object*>* BinaryParser::get_tuple(){
   int length = m_bufferIns->read_int();
   String* str;
   std::vector<Object*>* list = new std::vector<Object*>();

   for(int i = 0;i<length;i++){
       char obj_type = m_bufferIns->read();
       switch (obj_type)
       {
       case 'c':
           std::cout << "get a code object"<<std::endl;
           list->push_back(getCodeObject());
           break;
       case 'i':
           list->push_back(new Integer(m_bufferIns->read_int()));
           break;
       case 'N':
           list->push_back(NULL);
           break;
       case 't':
            str = getString();
            list->push_back(str);
            m_string_table.push_back(str);
            break;
       case 's':
            list->push_back(getString());
            break;
       case 'R':
            list->push_back(m_string_table.at(m_bufferIns->read_int()));
            break;
       default:
            throw std::logic_error("unknow style in binary code file");
            break;
       }
   }
   return list;
}
std::vector<Object*>* BinaryParser::getNames(){
   if (m_bufferIns->read() == '(') {
        return get_tuple();
    }

    m_bufferIns->back();
    return NULL;
}
std::vector<Object*>* BinaryParser::getArgList(){
    if (m_bufferIns->read() == '(') {
        return get_tuple();
    }

    m_bufferIns->back();
    return NULL;
}
std::vector<Object*>* BinaryParser::getFreeVars(){
    if (m_bufferIns->read() == '(') {
        return get_tuple();
    }

    m_bufferIns->back();
    return NULL;
}
std::vector<Object*>* BinaryParser::getCellVars(){
    if (m_bufferIns->read() == '(') {
        return get_tuple();
    }

    m_bufferIns->back();
    return NULL;
}
String* BinaryParser::getFileName(){
    char ch = m_bufferIns->read();

    if (ch == 's') {
        return getString();
    }
    else if (ch == 't') {
        String* str = getString();
        m_string_table.push_back(str);
        return str;
    }
    else if (ch == 'R') {
        return m_string_table.at(m_bufferIns->read_int());
    }
    return NULL;
}
String* BinaryParser::getModuleName(){
    return getFileName();
}
String* BinaryParser::getNoTable(){
   char ch = m_bufferIns->read();
    
    if (ch != 's' && ch != 't') {
        m_bufferIns->back();
        return NULL;
    }

    return getString(); 
}

}