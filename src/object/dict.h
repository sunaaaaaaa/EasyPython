#ifndef __EASY_PYTHON_VM_DICT_H_
#define __EASY_PYTHON_VM_DICT_H_
#include "object.h"
#include "Klass.h"
#include "../util/map.h"
#include <vector>
namespace easy_vm{

class DictKlass:public Klass{
private:
    DictKlass();
    static DictKlass* instance;
public:
    static DictKlass* getInstance();
    void init();

    virtual void print(Object* obj);
    virtual Object* subscr(Object* obj,Object* index);
    virtual void storeSubscr(Object* obj,Object* index,Object* value);
    virtual void delSubscr(Object* obj,Object* ele);
    virtual Object* contains(Object* obj,Object* ele);
    virtual Object* iter(Object* obj);
    virtual Object* allocateInstance(std::vector<Object*>* args);  
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
public:
    static Object* dict_set_default(std::vector<Object*>* args);
    static Object* dict_delete(std::vector<Object*>* args);
    static Object* dict_keys(std::vector<Object*>* args);
    static Object* dict_values(std::vector<Object*>* args);
    static Object* dict_items(std::vector<Object*>* args);
    static Object* dict_iterkeys(std::vector<Object*>* args);
    static Object* dict_itervalues(std::vector<Object*>* args);
    static Object* dict_iteritems(std::vector<Object*>* args);        
private:
    Map<Object*,Object*>* m_map;
};

}

#endif