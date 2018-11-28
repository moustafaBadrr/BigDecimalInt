#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

const int ASCII_0 = 48;
const int ASCII_9 = 57;

#ifndef BIGDECIMALINT_H
#define BIGDECIMALINT_H

class BigDecimalInt
{
private:
    string string_number;
    char sign;
    void check_input(string checked_num);
    void save_sign(string sent_string);
    void save_sign(int number);
    string remove_sign(string sent_string);
    int absolute(int number);
    int count_digits(int number);
    string int_to_string(int number, int num_of_digits);
    int to_digit(char c);
    char to_ASCII(int num);
    string ninth_complement(string string_number);
    string add_one_to_string(string string_number);
    string tenth_complement(string string_number);
    string add_two_string_numbers(const string& string_number1, const string& string_number2);
    void make_size_equal(string& string1, string& string2);
    void add_0s_to_end(string& str, int num_of_0s);

public:

    BigDecimalInt();
    BigDecimalInt(string dec_str);
    BigDecimalInt(int dec_int);
    friend bool operator> (const BigDecimalInt& big1, const BigDecimalInt& big2);
    friend bool operator< (const BigDecimalInt& big1, const BigDecimalInt& big2);
    friend bool operator== (const BigDecimalInt& big1, const BigDecimalInt& big2);
    friend BigDecimalInt operator+(const BigDecimalInt& big1,const BigDecimalInt& big2);
    friend BigDecimalInt operator-(const BigDecimalInt& big1,const BigDecimalInt& big2);
    friend ostream& operator<<(ostream& out,const BigDecimalInt& big);
};

#endif // BIGDECIMALINT_H
