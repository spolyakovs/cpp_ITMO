#include ".hpp"
#include <iostream>


class safe_c_array_t <T> {
  private:
    T* array;

  public:
    safe_c_array_t(std::size_t num){
      this->array = new safe_long_long_t[num];
    };


    void operator new (int size){
      this->array = ::new safe_c_array_t(size);
    };

    safe_long_long_t operator[] (int number){
      return
    };

    void operator delete(void * p)
    {
        ::delete(p);
    };
}
