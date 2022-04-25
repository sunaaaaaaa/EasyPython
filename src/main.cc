#include <iostream>
#include "util/buffer_input_stream.h"
#include "code/code_object.h"
#include "code/binary_parser.h"

int main(){
    easy_vm::BufferedInputStream stream("hello.pyc");

    easy_vm::BinaryParser parser(&stream);

    easy_vm::CodeObject* code = parser.parse();
    return 0;
}