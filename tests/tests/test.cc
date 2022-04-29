#include <iostream>
#include <vector>
class Parent{

};

class Son:public Parent{

};

int main(){
  int length = 5;

  while(length--){
    std::cout << length << std::endl;
  }
  length = 5;
  int* a = &length;
  int* b = &length;
  if(a==b){
    std::cout << "aa" << std::endl;
  }
  std::vector<Parent*>* vector = new std::vector<Parent*>(length);
  for(int i = 0;i<length;i++){
      Son* a = new Son();
      vector->push_back(a); 
  }

  std::cout << length <<std::endl;
  std::cout << vector->size() << std::endl; 

}