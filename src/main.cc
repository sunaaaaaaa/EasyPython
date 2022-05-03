#include <iostream>
#include "util/buffer_input_stream.h"
#include "code/code_object.h"
#include "code/binary_parser.h"
#include "runtime/interpreter.h"
int main(){
    easy_vm::BufferedInputStream stream("../tests/test_global.pyc");
    easy_vm::BinaryParser parser(&stream);
    
    easy_vm::CodeObject* code = parser.parse();
    
    easy_vm::Interpreter inter;
    inter.run(code);
    return 0;
}