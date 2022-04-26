#ifndef __EASY_PYTHON_VM_BUFFER_INPUT_H_
#define __EASY_PYTHON_VM_BUFFER_INPUT_H_
#include <stdio.h>
#include <iostream>
#define BUFFER_LEN 256
namespace easy_vm{

class BufferedInputStream{
public:
   BufferedInputStream(char const* filename){
       m_fp = fopen(filename,"rb");
       if(!m_fp){
           perror("fail");
           throw std::logic_error("Error: cannot open this file");
       }
       fread(m_buffer, sizeof(char),BUFFER_LEN,m_fp);
   }

   ~BufferedInputStream(){
       close();
   }

   char read(){
       if(m_index < BUFFER_LEN){
           return m_buffer[m_index++];
       }else{
           //当缓冲区的内容已经读取完毕，读取下一段内容
           m_index = 0;
           fread(m_buffer, sizeof(char),BUFFER_LEN,m_fp);
           return m_buffer[m_index++];
       }
   }
   //因为python的字节码文件为大端方式，因此后面的字符是在高地址上，因此第四个字节是地址最高的
   int read_int(){
       int b1 = read() & 0xff;
       int b2 = read() & 0xff;
       int b3 = read() & 0xff;
       int b4 = read() & 0xff;
       return b4 << 24 | b3 << 16 | b2 << 8 | b1;
   }
    
   //回退
   void back(){
       --m_index;
   }

   void close(){
       if(m_fp != NULL){
           fclose(m_fp);
           m_fp = NULL;
       }
   }
private:
    FILE* m_fp;
    char m_buffer[BUFFER_LEN];
    unsigned short m_index = 0;
};
}

#endif