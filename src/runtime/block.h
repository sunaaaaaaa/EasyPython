#ifndef __EASY_PYTHON_VM_BLOCK_H_
#define __EASY_PYTHON_VM_BLOCK_H_

//表示一个语句块
namespace easy_vm{

struct Block{
    unsigned char m_type; //语句块的类型，while块、if块等等
    unsigned char m_target;//该语句块，break之后要跳转到的地址
    int m_level;//该语句块的深度，即嵌套循环、嵌套if等
    Block():m_type(0),m_target(0),m_level(0){}
    Block(unsigned char type,unsigned char target,int level):m_type(type),m_target(target),m_level(level){}
    Block(const Block& block){
        m_type = block.m_type;
        m_target = block.m_target;
        m_level = block.m_level;
    }
};    
}
#endif