#include "map.h"
#include <iostream>
#include "../object/object.h"
#include "../runtime/universe.h"
namespace easy_vm{

template<class K,class V>
Map<K,V>::Map(){
    m_entries = new MapEntry<K, V>[8];
    m_length  = 8;
    m_size    = 0;
}

template <typename K, typename V>
MapEntry<K, V>::MapEntry(const MapEntry<K, V>& entry) {
    m_k = entry.m_k;
    m_v = entry.m_v;
}


template <typename K, typename V>
void Map<K, V>::put(K k, V v) {
    for (int i = 0; i < m_size; ++i) {
        if (m_entries[i].m_k->equal(k) == (Object*)Universe::True) {
            m_entries[i].m_v = v;
            return;
        }
    }
    
    expand();
    m_entries[m_size++] = MapEntry<K, V>(k, v);
}


template <typename K, typename V>
V Map<K, V>::get(K k) {
    int i = index(k);
    if (i < 0){
        return Universe::None;
    }else{
        return m_entries[i].m_v;   
    }
}

template <typename K, typename V>
bool Map<K, V>::has_key(K k) {
    int i = index(k);
    return i >= 0;
}

template <typename K, typename V>
int Map<K, V>::index(K k) {
    for (int i = 0; i < m_size; i++) {
        if (m_entries[i].m_k->equal(k) == (Object*)Universe::True) {
            return i;
        }
    }

    return -1;
}

template <typename K, typename V>
void Map<K, V>::expand() {
    if (m_size >= m_length) {
        MapEntry<K, V>* new_entries = new MapEntry<K, V>[m_length << 1];
        for (int i = 0; i < m_size; i++) {
            new_entries[i] = m_entries[i];
        }
        m_length <<= 1;
        //delete[] m_entries;
        m_entries = new_entries;
    }
}


template <typename K, typename V>
V Map<K, V>::remove(K k) {
    int i = index(k);
    if (i < 0)
        return 0; 
    V v = m_entries[i].m_v;
    m_entries[i] = m_entries[--m_size];
    return v;
}

template <typename K, typename V>
K Map<K, V>::get_key(int index) {
    return m_entries[index].m_k;
}

template <typename K, typename V>
V Map<K, V>::get_value(int index) {
    return m_entries[index].m_v;
}

template class Map<Object*, Object*>;

}