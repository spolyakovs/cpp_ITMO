#include <iostream>


template <typename T> class safe_c_array_t {
  private:
    T *array;
    std::size_t size;

  public:
    /*explicit ??? */safe_c_array_t(std::size_t size);

    safe_c_array_t(safe_c_array_t &copy_from);

    ~safe_c_array_t();

    T &get_array();

    std::size_t get_size();


    void *operator new(std::size_t size);

    void operator delete(void *ptr);


    void operator= (safe_c_array_t other_array);

    T &operator[] (std::size_t idx);
  };
