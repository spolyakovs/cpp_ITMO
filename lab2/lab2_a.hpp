#pragma once

#include <iostream>

class safe_long_long_t {
  private:
    long long value;

  public:
    safe_long_long_t(long long number);
    safe_long_long_t();

    //getter
    long long& get_value();

    //assignment operators
    void operator= (long long number);
    // a++
    safe_long_long_t operator++();
    //++a, why                 "int"       ?????????
    safe_long_long_t operator++(int);
    // a--
    safe_long_long_t operator--();
    //--a
    safe_long_long_t operator--(int);

    friend std::ostream& operator<< (std::ostream &output, safe_long_long_t number);
    friend std::istream& operator>> (std::istream &input, safe_long_long_t &number);
};


//comparative operators
bool operator== (safe_long_long_t number1, safe_long_long_t number2);

bool operator!= (safe_long_long_t number1, safe_long_long_t number2);

bool operator> (safe_long_long_t number1, safe_long_long_t number2);

bool operator>= (safe_long_long_t number1, safe_long_long_t number2);

bool operator< (safe_long_long_t number1, safe_long_long_t number2);

bool operator<= (safe_long_long_t number1, safe_long_long_t number2);


//math operators with =
void operator+= (safe_long_long_t &number1, safe_long_long_t number2);

void operator-= (safe_long_long_t &number1, safe_long_long_t number2);

void operator*= (safe_long_long_t &number1, safe_long_long_t number2);

void operator/= (safe_long_long_t &number1, safe_long_long_t number2);

void operator%= (safe_long_long_t &number1, safe_long_long_t number2);


//math operators without =
safe_long_long_t operator+ (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator- (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator* (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator/ (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator% (safe_long_long_t number1, safe_long_long_t number2);


//input/output operators
std::ostream& operator<< (std::ostream& output, safe_long_long_t number);

std::istream& operator>> (std::istream& input, safe_long_long_t& number);
