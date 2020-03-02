#pragma once
#include <iostream>

template <class T>
  class safe_c_array_t{
    private:
      T* array;

    public:
      safe_c_array_t(int num);

      void* operator new(std::size_t size);

      T operator[] (std::size_t size);

      void operator delete(void* p);
  };
