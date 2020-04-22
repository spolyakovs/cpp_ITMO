#pragma once

#include "lab2_b.hpp"

template <typename T>
safe_c_array_t<T>::safe_c_array_t (std::size_t new_size) {
  size = new_size;
  array = new T[size];
}

template <typename T>
safe_c_array_t<T>::safe_c_array_t (const safe_c_array_t<T> &copy_from) {
  size = copy_from.size;
  array = new T[size];
  for (int i = 0; i < size; i++) {
    array[i] = copy_from[i];
  }
}

template <typename T>
safe_c_array_t<T>::~safe_c_array_t() {
  delete[] array;
}

template <typename T>
T *safe_c_array_t<T>::get_array() {
  return array;
}

template <typename T>
std::size_t safe_c_array_t<T>::get_size() {
  return size;
}

template <typename T>
void safe_c_array_t<T>::operator= (const safe_c_array_t<T> &other) {
  size = other.size;
  delete[] array;
  array = new T[size];
  for (int i = 0; i < size; ++i) {
    array[i] = other[i];
  }
}

template <typename T>
T &safe_c_array_t<T>::operator[] (std::size_t idx) {
  return array[idx];
}

template <typename T>
T safe_c_array_t<T>::operator[] (std::size_t idx) const {
  return array[idx];
}
