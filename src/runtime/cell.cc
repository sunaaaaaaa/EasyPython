#include "cell.h"
#include "../object/String.h"
#include "../object/dict.h"
namespace easy_vm{

CellKlass* CellKlass::instance = NULL;

CellKlass* CellKlass::getInstance(){
    if(instance == NULL){
        instance = new CellKlass();
    }
    return instance;
}

CellKlass::CellKlass(){
    setKlassDict(new Dict());
    setName(new String("cell"));
}

Cell::Cell(List* list,int idx):m_table(list),m_index(idx){
    setKlass(CellKlass::getInstance());
}

Object* Cell::getValue(){
    return m_table->get(m_index);
}

} // namespace easy_vm