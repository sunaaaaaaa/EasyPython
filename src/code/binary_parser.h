#ifndef __EASY_PYTHON_VM_BINARY_PARSER_H_
#define __EASY_PYTHON_VM_BINARY_PARSER_H_
#include "../util/buffer_input_stream.h"
#include "code_object.h"
namespace easy_vm{
class BinaryParser{
public:
   BinaryParser(BufferedInputStream* stream);
   CodeObject* parse();
   ~BinaryParser();
private:
    void initCodeObject();
    CodeObject* getCodeObject();
    String* getByteCode();
    std::vector<Object*>* getConsts();
    std::vector<Object*>* getNames();
    std::vector<Object*>* getArgList();
    std::vector<Object*>* getFreeVars();
    std::vector<Object*>* getCellVars();
    String* getFileName();
    String* getModuleName();
    String* getNoTable();
    String* getString();
    std::vector<Object*>* get_tuple(); 
private:
   BufferedInputStream* m_bufferIns;
   //CodeObject* m_codeObject;
   std::vector<String*> m_string_table;
};    
}

#endif