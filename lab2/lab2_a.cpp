#include ".hpp"
#include <iostream>


class safe_long_long_t{
  private:
    long long value;

  public:
    //CONSTRUCTORS
    safe_long_long_t(long long number) {
      value = number;
    };
    safe_long_long_t() {
      value = 0;
    };

    //GETTER
    long long& get_value(){
      return value;
    };

    //ASSIGNMENT OPERATORS
    void operator= (long long number) {
      this->value = number;
    };
    // a++
    safe_long_long_t operator++(){
        this->value++;
        return this->value;
    };
    //++a, why                 "int"       ?????????
    safe_long_long_t operator++(int){
      ++(this->value);
      return this->value;
    };
    // a--
    safe_long_long_t operator--(){
        this->value--;
        return this->value;
    };
    //--a
    safe_long_long_t operator--(int){
      --(this->value);
      return this->value;
    };

    static safe_long_long_t& operator[] (int number){
      return ptr[number];
    };


    friend std::ostream& operator<< (std::ostream &output, safe_long_long_t number);
    friend std::istream& operator>> (std::istream &input, safe_long_long_t &number);
};


//COMPARATIVE OPERATORS
bool operator== (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() == number2.get_value());
};

bool operator!= (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() != number2.get_value());
};

bool operator> (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() > number2.get_value());
};

bool operator>= (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() >= number2.get_value());
};

bool operator< (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() < number2.get_value());
};

bool operator<= (safe_long_long_t number1, safe_long_long_t number2) {
  return (number1.get_value() <= number2.get_value());
};


//MATH OPERATORS WITH =
void operator+= (safe_long_long_t &number1, safe_long_long_t number2) {
  number1.get_value() += number2.get_value();
};

void operator-= (safe_long_long_t &number1, safe_long_long_t number2) {
  number1.get_value() -= number2.get_value();
};

void operator*= (safe_long_long_t &number1, safe_long_long_t number2) {
  number1.get_value() *= number2.get_value();
};

void operator/= (safe_long_long_t &number1, safe_long_long_t number2) {
  number1.get_value() /= number2.get_value();
};

void operator%= (safe_long_long_t &number1, safe_long_long_t number2) {
  number1.get_value() %= number2.get_value();
};

//MATH OPERATORS WITHOUT =
safe_long_long_t operator+ (safe_long_long_t number1, safe_long_long_t number2) {
  return safe_long_long_t(number1.get_value() + number2.get_value());
};

safe_long_long_t operator- (safe_long_long_t number1, safe_long_long_t number2) {
  return safe_long_long_t(number1.get_value() - number2.get_value());
};

safe_long_long_t operator* (safe_long_long_t number1, safe_long_long_t number2) {
  return safe_long_long_t(number1.get_value() * number2.get_value());
};

safe_long_long_t operator/ (safe_long_long_t number1, safe_long_long_t number2) {
  return safe_long_long_t(number1.get_value() / number2.get_value());
};

safe_long_long_t operator% (safe_long_long_t number1, safe_long_long_t number2) {
  return safe_long_long_t(number1.get_value() % number2.get_value());
};


//INPUT/OUTPUT OPERATORS
std::ostream& operator<< (std::ostream &output, safe_long_long_t number) {
  output << number.get_value();
  return output;
};

std::istream& operator>> (std::istream &input, safe_long_long_t &number) {
  long long temp;
  input >> temp;
  number.get_value() = temp;
};


int main(){
  //TESTS
  safe_long_long_t number1, number1_equal, number2, number3;
  number1 = 1025;
  number1_equal = 1025;
  number2 = 1024000;

/*
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
  number3 = number1 - number2;
  std::cout << number1 << " - " << number2 << " = " << number3 << std::endl;
  number3 = number1 * number2;
  std::cout << number1 << " * " << number2 << " = " << number3 << std::endl << std::endl;
  number3 = number2 / number1;
  std::cout << number2 << " / " << number1 << " = " << number3 << std::endl;

  std::cout << "number1 == number2: " << (number1 == number2) << std::endl;
  std::cout << "number1 == number1_equal: " << (number1 == number1_equal) << std::endl;
  std::cout << "number1 != number2: " << (number1 != number2) << std::endl;
  std::cout << "number1 != number1_equal: " << (number1 != number1_equal) << std::endl;
  std::cout << "number1 > number2: " << (number1 > number2) << std::endl;
  std::cout << "number2 > number1: " << (number2 > number1) << std::endl;
  std::cout << "number1 >= number2: " << (number1 >= number2) << std::endl;
  std::cout << "number1 >= number1_equal: " << (number1 >= number1_equal) << std::endl;
  std::cout << "number1 < number2: " << (number1 < number2) << std::endl;
  std::cout << "number2 < number1: " << (number2 < number1) << std::endl;
  std::cout << "number1 <= number2: " << (number1 <= number2) << std::endl;
  std::cout << "number1 <= number1_equal: " << (number1 <= number1_equal) << std::endl <<  std::endl;

  std::cin >> number3;
  std::cout << number3 << std::endl;

  std::cout << "number1 == number2: " << (number1 == number2) << std::endl;
  std::cout << "number1 == number1_equal: " << (number1 == number1_equal) << std::endl;
  std::cout << "5 == number1: " << (5 == number1) << std::endl;
  std::cout << "1025 == number1: " << (1025 == number1) << std::endl;
*/
  return 0;
};
