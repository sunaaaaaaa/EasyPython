#ifndef __EASY_PYTHON_VM_OOP_CLOSURE_H_
#define __EASY_PYTHON_VM_OOP_CLOSURE_H_

namespace easy_vm{
class Space;
class Heap;

class Object;
class Klass;

template <typename T>
class ArrayList;

template <typename K, typename V>
class Map;

template <typename T>
class Stack;


//垃圾回收算法，引用计数
class OopClosure{
public:
    virtual void do_oop(Object** obj) = 0;
    virtual void do_array_list(ArrayList<Klass*>** list) = 0;
    virtual void do_array_list(ArrayList<Object*>** list) = 0;
    virtual void do_map(Map<Object*,Object*>** map) = 0;
    virtual void do_raw_mem(char** mem,int length) = 0;
    virtual void do_klass(Klass** kls) = 0;
};

class ScanvengeOopClosure:public OopClosure{
public:
    ScanvengeOopClosure(Space* from,Space* to,Space* meta);
    virtual ~ScanvengeOopClosure();
    virtual void do_oop(Object** obj);
    virtual void do_array_list(ArrayList<Klass*>** list);
    virtual void do_array_list(ArrayList<Object*>** list);
    virtual void do_map(Map<Object*,Object*>** map);
    virtual void do_raw_mem(char** mem,int length);
    virtual void do_klass(Klass** kls);
    
    //扫描
    void scavenge();
    void process_roots();
private:
    Object* copy_and_push(Object* obj);     
private:
    Space* m_from;
    Space* m_to;
    Space* m_meta;
    Stack<Object*>* m_oop_stack;  
};
}

#endif