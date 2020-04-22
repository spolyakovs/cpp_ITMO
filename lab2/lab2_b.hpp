#pragma once

#include <iostream>

template <typename T>
class safe_c_array_t {
private:
  T *array;
  std::size_t size;

public:
  explicit safe_c_array_t(std::size_t size);

  safe_c_array_t(const safe_c_array_t &copy_from);

  ~safe_c_array_t();

  T *get_array();

  std::size_t get_size();

  void operator delete(void *ptr);

  void operator= (const safe_c_array_t<T> &other);

  T &operator[] (std::size_t idx);
  T operator[] (std::size_t idx) const;
};
