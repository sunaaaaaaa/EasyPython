#include "universe.h"
#include "../object/List.h"
#include "../object/dict.h"
#include "../object/String.h"
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
    StringKlass::getInstance()->init();
    DictKlass::getInstance()->init();
    IntegerKlass::getInstance();
    ListKlass::getInstance()->init();
    StringKlass::getInstance()->orderSuper();
    DictKlass::getInstance()->orderSuper();
    IntegerKlass::getInstance()->orderSuper();
    ListKlass::getInstance()->orderSuper();
}
void Universe::destory(){
    
}

}