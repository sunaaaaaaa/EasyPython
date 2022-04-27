#ifndef __EASY_PYTHON_VM_MAP_H_
#define __EASY_PYTHON_VM_MAP_H_

namespace easy_vm{

template<class K,class V>
class MapEntry{
public:
    K m_k;
    V m_v;

    MapEntry(const MapEntry<K,V>& entry);
    MapEntry(K k,V v):m_k(k),m_v(v){}
    MapEntry():m_k(0),m_v(0){}
};

template<class K,class V>
class Map{
public:
   Map();
   int size()const{return m_size;}
   void put(K k,V v);
   V get(K k);
   K get_key(int index);
   bool has_key(K k);
   V remove(K k);
   int index(K k);
   MapEntry<K,V>* entries(){return m_entries;}
private:
   void expand();
private:
   MapEntry<K,V>* m_entries;
   int m_size;
   int m_length;
};
}
#endif