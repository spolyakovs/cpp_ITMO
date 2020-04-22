#pragma once

#include "lab2_b.tpp"

int main() {
  // tests
  int size = 5;

  safe_c_array_t<int> safe_array = safe_c_array_t<int>(size);

  safe_c_array_t<int> array(size);
  safe_c_array_t<int> array_copy(array);
  safe_c_array_t<int> new_array(size);

  for (int i = 0; i < size; ++i) {
    array[i] = i + 1;
    array_copy[i] = i + 1;
  }

  new_array = array;

  for (int i = 0; i < size; ++i) {
    std::cout << "i: " << i << std::endl;
    std::cout << "safe_array[i] before redefinition: " << safe_array[i] << std::endl;
    std::cout << "new_array[i] before redefinition: " << new_array[i] << std::endl;
    std::cout << "array_copy[i] before redefinition: " << array_copy[i] << std::endl;

    array_copy[i] = i + 11;
    std::cout << "safe_array[i] after redefinition: " << safe_array[i] << std::endl;
    std::cout << "new_array[i] after redefinition: " << new_array[i] << std::endl;
    std::cout << "array_copy[i] after redefinition: " << array_copy[i] << std::endl;
    std::cout << std::endl;
  }
}
