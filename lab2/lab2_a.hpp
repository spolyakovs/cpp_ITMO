class safe_long_long_t{
  private:
    long long value;

  public:
    safe_long_long_t(long long number);
    safe_long_long_t();

    //GETTER
    long long& get_value();

    //ASSIGNMENT OPERATORS
    void operator= (long long number);
    // a++
    safe_long_long_t operator++();
    //++a, why                 "int"       ?????????
    safe_long_long_t operator++(int);
    // a--
    safe_long_long_t operator--();
    //--a
    safe_long_long_t operator--(int);

    static safe_long_long_t& operator[] (int number);

};


//COMPARATIVE OPERATORS
bool operator== (safe_long_long_t number1, safe_long_long_t number2);

bool operator!= (safe_long_long_t number1, safe_long_long_t number2);

bool operator> (safe_long_long_t number1, safe_long_long_t number2);

bool operator>= (safe_long_long_t number1, safe_long_long_t number2);

bool operator< (safe_long_long_t number1, safe_long_long_t number2);

bool operator<= (safe_long_long_t number1, safe_long_long_t number2);


//MATH OPERATORS WITH =
void operator+= (safe_long_long_t &number1, safe_long_long_t number2);

void operator-= (safe_long_long_t &number1, safe_long_long_t number2);

void operator*= (safe_long_long_t &number1, safe_long_long_t number2);

void operator/= (safe_long_long_t &number1, safe_long_long_t number2);

void operator%= (safe_long_long_t &number1, safe_long_long_t number2);

//MATH OPERATORS WITHOUT =
safe_long_long_t operator+ (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator- (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator* (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator/ (safe_long_long_t number1, safe_long_long_t number2);

safe_long_long_t operator% (safe_long_long_t number1, safe_long_long_t number2);


//INPUT/OUTPUT OPERATORS
std::ostream& operator<< (std::ostream &output, safe_long_long_t number);

std::istream& operator>> (std::istream &input, safe_long_long_t &number);
