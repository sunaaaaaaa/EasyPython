#ifndef __EASY_PYTHON_VM_DICT_H_
#define __EASY_PYTHON_VM_DICT_H_
#include "object.h"
#include "Klass.h"
#include "../util/map.h"
namespace easy_vm{

class DictKlass:public Klass{
private:
    DictKlass(){}
    static DictKlass* instance;
public:
    static DictKlass* getInstance(); 
    virtual void print(Object* obj);
    // virtual Object* subscr(Object* obj,Object* index);
    // virtual Object* contains(Object* obj,Object* ele);   
};

class Dict:public Object{
friend class DictKlass;
public:
    Dict();
    Dict(Map<Object*,Object*>* map);
    
    Map<Object*,Object*>* getMap(){return m_map;}
    void put(Object* k,Object* v){ m_map->put(k,v);}
    Object* get(Object* k){return m_map->get(k);}
    bool hasKey(Object* k){return m_map->has_key(k);}
    int size(){return m_map->size();}
    Object* remove(Object* k){return m_map->remove(k);}
    void update(Dict* dict);
private:
    Map<Object*,Object*>* m_map;
};

}

#endif