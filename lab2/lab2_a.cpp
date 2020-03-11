#include "lab2_a.hpp"


//definition "safe_long_long_t" class methods

//constructors
safe_long_long_t::safe_long_long_t(long long number) {
  value = number;
};
safe_long_long_t::safe_long_long_t() {
  value = 0;
};

//getter
long long &safe_long_long_t::get_value() {
  return value;
};

//assignment operator
void safe_long_long_t::operator= (safe_long_long_t number) {
  value = number.get_value();
};

// подумать над возвратом
// ++a
safe_long_long_t safe_long_long_t::operator++() {
  ++value;
};
// a++
safe_long_long_t safe_long_long_t::operator++(int) {
  value++;
};
// --a
safe_long_long_t safe_long_long_t::operator--() {
  --value;
};
// a--
safe_long_long_t safe_long_long_t::operator--(int) {
  value--;
};

//math operators with =
safe_long_long_t &safe_long_long_t::operator+= (safe_long_long_t number) {
  value += number.get_value();
  return *this;
};

safe_long_long_t &safe_long_long_t::operator-= (safe_long_long_t number) {
  value -= number.get_value();
  return *this;
};

safe_long_long_t &safe_long_long_t::operator*= (safe_long_long_t number) {
  value *= number.get_value();
  return *this;
};

safe_long_long_t &safe_long_long_t::operator/= (safe_long_long_t number) {
  value /= number.get_value();
  return *this;
};

safe_long_long_t &safe_long_long_t::operator%= (safe_long_long_t number) {
  value %= number.get_value();
  return *this;
};


//comparative operators
bool operator== (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() == number2.get_value());
};

bool operator!= (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() != number2.get_value();
};

bool operator> (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() > number2.get_value();
};

bool operator>= (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() >= number2.get_value();
};

bool operator< (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() < number2.get_value();
};

bool operator<= (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() <= number2.get_value();
};

//math operators without =
safe_long_long_t operator+ (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() + number2.get_value();
};

safe_long_long_t operator- (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() - number2.get_value();
};

safe_long_long_t operator* (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() * number2.get_value();
};

safe_long_long_t operator/ (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() / number2.get_value();
};

safe_long_long_t operator% (safe_long_long_t number1, safe_long_long_t number2) {
  return number1.get_value() % number2.get_value();
};


//input/output operators
std::ostream &operator<< (std::ostream &output, safe_long_long_t number) {
  output << number.get_value();
  return output;
};

std::istream &operator>> (std::istream &input, safe_long_long_t &number) {
  long long temp;
  input >> temp;
  number.get_value() = temp;
};


int main() {
  //tests
  safe_long_long_t number1, number1_equal, number2, number3;
  number1 = 1025;
  number1_equal = 1025;
  number2 = 1024000;


  std::cout << "number1++: " << number1++ << std::endl;
  std::cout << "++number1: " << ++number1 << std::endl;
  std::cout << "number1--: " << number1-- << std::endl;
  std::cout << "--number1: " << --number1 << std::endl;

  std::cout << "number1 = " << number1 << std::endl;
  std::cout << "number2 = " << number2 << std::endl << std::endl;

  number3 = 5 + number1;
  std::cout << "5 + " << number1 << " = " << number3 << std::endl;
  std::cout << "number3 = " << number3 << std::endl;
  std::cout << "number3 += number2" << std::endl;
  number3 += number2;
  std::cout << "number3 = " << number3 << std::endl;
  number3 = number1 + number2;
  std::cout << number1 << " + " << number2 << " = " << number3 << std::endl;

  std::cout << "number1 == number2: " << (number1 == number2) << std::endl;
  std::cout << "number1 == number1_equal: " << (number1 == number1_equal) << std::endl;
  std::cout << "number1 != number2: " << (number1 != number2) << std::endl;
  std::cout << "number1 != number1_equal: " << (number1 != number1_equal) << std::endl;

  std::cin >> number3;
  std::cout << number3 << std::endl;

  std::cout << "number1 == number2: " << (number1 == number2) << std::endl;
  std::cout << "number1 == number1_equal: " << (number1 == number1_equal) << std::endl;
  std::cout << "5 == number1: " << (5 == number1) << std::endl;
  std::cout << "1025 == number1: " << (1025 == number1) << std::endl;

  return 0;
};
