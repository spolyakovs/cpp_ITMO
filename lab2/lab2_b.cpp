#include <iostream>


template <typename T> class safe_c_array_t {
  private:
    T *array;

  public:
    safe_c_array_t<T>(std::size_t size) {
      array = new T[size];
    };

    safe_c_array_t<T>(safe_c_array_t<T> &safe_array) {
      array = new T[sizeof(safe_array.get_array())];
    };

    ~safe_c_array_t() {
      delete array;
    };

    T &get_array() {
      return &array;
    };


    void *operator new(std::size_t size) {
      void *ptr;
      ptr = std::malloc(size);
      if (!ptr) {
        throw std::bad_alloc();
      };
      return ptr;
    };

    void operator delete(void *ptr) {
      std::free(ptr);
    };

    T &operator[](std::size_t idx) {
      return array[idx];
    };
  };


int main() {
  // tests
  int size = 5;

  safe_c_array_t<int> *array_pointer = new safe_c_array_t<int>(size);
  delete array_pointer;

  safe_c_array_t<int> array(size);
  safe_c_array_t<int> array_copy(array);

  safe_c_array_t<int> temp(1);
  for (int i = 0; i < size; ++i) {
    array[i] = i + 1;
    int value = array[i];
    std::cout << value << std::endl;
  };
};
