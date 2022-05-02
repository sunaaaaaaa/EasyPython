#ifndef __EASY_PYTHON_VM_CELL_H_
#define __EASY_PYTHON_VM_CELL_H_
#include "../object/List.h"
#include "../object/Klass.h"
#include "../object/object.h"
namespace easy_vm{

class CellKlass:public Klass{
private:
    CellKlass();
    static CellKlass* instance;
public:
    static CellKlass* getInstance();

    //virtual void oop_do(OopClosure* closure,Object* obj);
    //virtual size_t size();    
};

class Cell:public Object{
friend class CellKlass;
private:
    List* m_table;//存放cell变量所在的closure表
    int m_index;//在表中的索引
public:
    Cell(List* list,int idx);
    Object* getValue();
    List* getClosureTable(){return m_table;}
    int getIndex(){return m_index;}
};

}

#endif