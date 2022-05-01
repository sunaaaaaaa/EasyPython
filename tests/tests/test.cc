#include <iostream>
#include <vector>
class Parent{

};

class Son:public Parent{

};

void test(){
  std::vector<int> vec(3,0);
  vec.insert(vec.begin()+1,3);
  std::cout << vec.at(1)<<std::endl; 
}

void test1(){
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

int getNum(){
   return 5;
}

int getNum2(){
  getNum();
}

int test2(){
  getNum2();
}

int main(){
  int a = test2();
  std::cout<<a<<std::endl;
}