#include "universe.h"
#include <stdio.h>
namespace easy_vm{

//变量定义
Integer* Universe::True = NULL;
Integer* Universe::False = NULL;
Object* Universe::None = NULL;

void Universe::genesis(){
    True = new Integer(1);
    False = new Integer(0);
    None = new Object();
}
void Universe::destory(){
    
}

}