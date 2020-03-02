#include "lab2_b.hpp"
#include <iostream>

safe_c_array_t::safe_c_array_t(int num){
  this->array = new T[num];
};

void* safe_c_array_t::operator new (std::size_t size){
  this->array = std::malloc(size);
};

T safe_c_array_t::operator[] (std::size_t idx){
  return this->array[idx];
};

void safe_c_array_t::operator delete(void* p)
{
    std::free(p);
};

int main(){
  //tests
  int size = 5;
  safe_c_array_t array = new safe_c_array_t<int>(size);
  for (i = 0; i < size; ++i){
    array[i] = i + 1;
    std::cout << array[i];
  };
  delete[] array;

};
