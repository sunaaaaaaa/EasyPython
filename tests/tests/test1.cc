#include "../src/util/buffer_input_stream.h"
#include <iostream>
int main(){
    easy_vm::BufferedInputStream bf("hello.pyc");
    // printf("0x %x\n",bf.read_int());
    std::cout <<std::hex<< bf.read_int() << std::endl;
}