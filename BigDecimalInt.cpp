#include "BigDecimalInt.h"

BigDecimalInt::BigDecimalInt()  // default constructor
{
}
BigDecimalInt::BigDecimalInt(string dec_str)  // constructor take the number as string
{
    check_input(dec_str);                //  check if the number contains a literal or not
    save_sign(dec_str);                  //  take the sign of the number
    dec_str = remove_sign(dec_str);      //  remove the sign of the number
    string_number = dec_str;             //  put the number in the original string(the string in our class)
}
BigDecimalInt::BigDecimalInt(int dec_int)      // constructor take the number as integer and convert it to string
{
    save_sign(dec_int);              // take the sign
    dec_int = absolute(dec_int);     // remove the sign
    int num_of_digits = count_digits(dec_int);  // count the digits to know the size of the string
    string_number = int_to_string(dec_int, num_of_digits);   // convert the integer to string
}
void BigDecimalInt::check_input(string checked_num)  // check the inputs if it has a literal or not
{
    /// check the first element if it contain anything except + , - , any integer number (0:9)
    if(checked_num[0] != '+' && checked_num[0] != '-' && !(checked_num[0] >= ASCII_0 && checked_num[0] <= ASCII_9))
    {
        exit(1);
    }
    /// check the string elements after the first element if it contain anything except integer number (0:9)
    /// because the first element can be + or -  but the other elements can't be that
    for(int i = 1; i < checked_num.size(); i++)
    {
        if(!(checked_num[i] >= ASCII_0 && checked_num[i] <= ASCII_9))
        {
            exit(1);
        }
    }
}
void BigDecimalInt::save_sign(string sent_string)   // take the sign of the number from string number
{
    if(sent_string[0] == '-')
    {
        sign = '-';
    }
    // here we can but the number include the positive sign or no, so if we haven't a + in the first we consider that it positive
    else if (sent_string[0] == '+' || (sent_string[0]>= ASCII_0 && sent_string[0] <= ASCII_9))
    {
        sign = '+';
    }
}
void BigDecimalInt::save_sign(int number)           // take the sign of the number from integer number
{
    if(number < 0)
    {
        sign = '-';
    }
    else
    {
        sign = '+';
    }
}
string BigDecimalInt::remove_sign(string sent_string)  // remove the sign from the string number
{
    if( sent_string[0] == '+' || sent_string[0] == '-' )
    {
        sent_string.erase(0,1);
    }
    return sent_string;
}
int BigDecimalInt::absolute(int number)                 // remove the sign from the integer number
{
    if(number >= 0)
    {
        return number;
    }
    else
    {
        return -1 * number;
    }
}
int BigDecimalInt::count_digits(int number)    // count the digits
{
    int num_of_digits = 0;
    while(number >= 0)
    {
        number = number / 10;
        num_of_digits++;
        if(number == 0)
        {
            break;
        }
    }
    return num_of_digits;
}
char BigDecimalInt::to_ASCII(int num)     // convert  number to character
{
    return (static_cast<char>(num) + '0');
}
int BigDecimalInt::to_digit(char c)      // convert the character to integer
{
    return static_cast<int>(c - '0');
}
string BigDecimalInt::int_to_string(int number, int num_of_digits)  // convert the  integer to string
{
    char temp_string[num_of_digits + 1]; /// because the char array starts from zero
    for(int i = num_of_digits - 1; i >= 0 ; i--)
    {
        int remainder = number % 10;
        temp_string[i] = to_ASCII(remainder);
        number = number / 10;
    }
    temp_string[num_of_digits] = '\0';
    return temp_string;
}
string BigDecimalInt::ninth_complement(string sent_string)    // convert the string to ninth complement to convert it to tenth
{
    int temp;
    for(int i = 0 ; i < sent_string.size() ; i++)
    {

        temp = 9 - to_digit(sent_string[i]);
        sent_string[i] = to_ASCII(temp);
    }
    return sent_string;
}
string BigDecimalInt::add_one_to_string(string sent_string)  // to convert the ninth complement to tenth
{
    int sum = 0;
    int carry = 0;
    sum = to_digit(sent_string[sent_string.size() - 1]) + 1;
    if(sum >= 10)
    {
        sum = sum - 10;
        carry = 1;
    }
    else
    {
        carry = 0;
    }
    sent_string[sent_string.size() - 1] = to_ASCII(sum);
    if(carry == 1)
    {
        for(int i = sent_string.size() - 2 ; i >= 0 ; i--)
        {
            sum = to_digit(sent_string[i]) + carry;
            if(sum >= 10)
            {
                sum = sum - 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            sent_string[i] = to_ASCII(sum);
        }
    }
    return sent_string;
}
string BigDecimalInt::tenth_complement(string sent_string)  // the tenth complement of the string
{
    sent_string = ninth_complement(sent_string);
    sent_string = add_one_to_string(sent_string);
    return sent_string;
}
string BigDecimalInt::add_two_string_numbers(const string& sent_string1, const string& sent_string2) // addition of two strings
{
    int sizee = sent_string1.size(); // OR sent_string2.size().
    int sum = 0;
    int carry = 0;
    string string_sum = sent_string1;
    // OR sent_string2 to make the size of the string equal sizee.
    sum = to_digit(sent_string1[sizee - 1]) + to_digit(sent_string2[sizee - 1]);
    if(sum >= 10)
    {
        sum = sum - 10;
        carry = 1;
    }
    string_sum[sizee - 1] = to_ASCII(sum);
    for(int i = sizee - 2 ; i >= 0 ; i--)
    {
        sum = to_digit(sent_string1[i]) + to_digit(sent_string2[i]) + carry;
        if(sum >= 10)
        {
            sum = sum - 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        string_sum[i] = to_ASCII(sum);
    }
    return string_sum;
}
void BigDecimalInt::add_0s_to_end(string& str, int num_of_0s)  // balance the two strings by add zeros to small string
{
    int temp_array_size = str.size() + num_of_0s;
    char temp_array[temp_array_size + 1];
    for(int i = temp_array_size - 1 ; i >= temp_array_size - str.size() ; i--)
    {
        temp_array[i] = str[i - num_of_0s];
    }
    for(int i = 0 ; i < num_of_0s ; i++)
    {
        temp_array[i] = '0';
    }
    temp_array[temp_array_size] = '\0';
    str = temp_array;
}
void BigDecimalInt::make_size_equal(string& string1, string& string2) // make the two strings equal in size by using above function
{

    int size1 = string1.size();
    int size2 = string2.size();
    if(size1 > size2)
    {
        add_0s_to_end(string2, size1 - size2);
    }
    else if(size2 > size1)
    {
        add_0s_to_end(string1, size2 - size1);
    }
}
bool operator>(const BigDecimalInt& big1, const BigDecimalInt& big2)  // overloaded function for greater than
{
    BigDecimalInt temp_big1 = big1;
    BigDecimalInt temp_big2 = big2;
    temp_big1.make_size_equal(temp_big1.string_number, temp_big2.string_number);
    // OR temp_big2.make_size_equal(......);
    int sizee = temp_big1.string_number.size(); // OR temp.big2.string_number.size().
    for(int i = 0 ; i < sizee ; i++)
    {
        if(temp_big1.to_digit(temp_big1.string_number[i])
                > temp_big2.to_digit(temp_big2.string_number[i]))
        {
            return true;
        }
        else if(temp_big1.to_digit(temp_big1.string_number[i])
                < temp_big2.to_digit(temp_big2.string_number[i]))
        {
            return false;
        }
    }
    return false;
}
bool operator<(const BigDecimalInt& big1, const BigDecimalInt& big2)  // overloaded function for smaller than
{

    BigDecimalInt temp_big1 = big1;
    BigDecimalInt temp_big2 = big2;
    temp_big1.make_size_equal(temp_big1.string_number, temp_big2.string_number);
    // OR temp_big2.make_size_equal(......);
    int sizee = temp_big1.string_number.size(); // OR temp.big2.string_number.size().
    for(int i = 0 ; i < sizee ; i++)
    {
        if(temp_big1.to_digit(temp_big1.string_number[i])
                < temp_big2.to_digit(temp_big2.string_number[i]))
        {
            return true;
        }
        if(temp_big1.to_digit(temp_big1.string_number[i])
                > temp_big2.to_digit(temp_big2.string_number[i]))
        {
            return false;
        }
    }
    return false;
}
bool operator==(const BigDecimalInt& big1, const BigDecimalInt& big2)   // overloaded function for equal
{

    BigDecimalInt temp_big1 = big1;
    BigDecimalInt temp_big2 = big2;
    temp_big1.make_size_equal(temp_big1.string_number, temp_big2.string_number);
    int sizee = temp_big1.string_number.size(); // OR temp.big2.string_number.size().
    for(int i = 0 ; i < sizee ; i++)
    {
        if(temp_big1.to_digit(temp_big1.string_number[i])
                != temp_big2.to_digit(temp_big2.string_number[i]))
        {
            return false;
        }
    }
    return true;
}
BigDecimalInt operator+(const BigDecimalInt& num1,const BigDecimalInt& num2)  // overloaded function to addition
{
    BigDecimalInt temp_string1 = num1;
    BigDecimalInt temp_string2 = num2;
    BigDecimalInt sum;
    //a Will make the size of temp_string1 = the size of temp_string2.
    // by adding 0s to the left size of the smaller string if exists.
    temp_string1.make_size_equal(temp_string1.string_number
                                 , temp_string2.string_number);

    if(temp_string1 > temp_string2)
    {
        sum.sign = temp_string1.sign;
    }
    else if(temp_string1 < temp_string2)
    {
        sum.sign = temp_string2.sign;
    }
    else if(temp_string1 == temp_string2)
    {
        if(temp_string1.sign == '+' || temp_string2.sign == '+')
        {
            sum.sign = '+';
        }
        else
        {
            sum.sign = '-';
        }
    }
    if(num1.sign == '-' && num2.sign == '-')
    {
        temp_string1.string_number = temp_string1.tenth_complement(temp_string1.string_number);
        temp_string2.string_number = temp_string2.tenth_complement(temp_string2.string_number);
    }
    else if(num1.sign == '-' && num2.sign == '+')
    {
        temp_string1.string_number = temp_string1.tenth_complement(temp_string1.string_number);
        // temp_string2.string_number STAY THE SAME.
    }
    else if(num1.sign == '+' && num2.sign == '-' )
    {
        // temp_string1.string_number STAY THE SAME.
        temp_string2.string_number = temp_string2.tenth_complement(temp_string2.string_number);
    }
    else
    {
        //temp_string1.string_number STAY THE SAME.
        //temp_string2.string_number STAY THE SAME.
    }
    sum.string_number = sum.add_two_string_numbers(temp_string1.string_number
                                                 , temp_string2.string_number);
    if (sum.sign == '-')
    {
        sum.string_number = sum.tenth_complement(sum.string_number);
    }
    return sum;
}
BigDecimalInt operator-(const BigDecimalInt& num1,const BigDecimalInt& num2)  // overloaded function to subtraction
{

    BigDecimalInt temp_string1 = num1;
    BigDecimalInt temp_string2 = num2;
    BigDecimalInt sum;
    // Will make the size of temp_string1 = the size of temp_string2.
    // by adding 0s to the left size of the smaller string if exists.
    temp_string1.make_size_equal(temp_string1.string_number
                                 , temp_string2.string_number);

    if(temp_string1 > temp_string2)
    {
        sum.sign = temp_string1.sign;
    }
    else if(temp_string1 < temp_string2)
    {
        if(temp_string2.sign == '+')
        {
            sum.sign = '-';
        }
        else
        {
            sum.sign = '+';
        }
    }
    else if(temp_string1 == temp_string2)
    {
        if(temp_string1.sign == '+' && temp_string2.sign == '+')
        {
            sum.sign = '+';
        }
        else if (temp_string1.sign == '+' &&  temp_string2.sign == '-')
        {
            sum.sign = '+';
        }
        else if (temp_string1.sign == '-' &&  temp_string2.sign == '+')
        {
            sum.sign = '-';
        }
        else
        {
            sum.sign = '+';
        }
    }
    if(num1.sign == '-' && num2.sign == '-')
    {
        temp_string1.string_number = temp_string1.tenth_complement(temp_string1.string_number);
        //temp_string1.string_number STAY THE SAME.
    }
    else if(num1.sign == '-' && num2.sign == '+')
    {
        temp_string1.string_number = temp_string1.tenth_complement(temp_string1.string_number);
        temp_string2.string_number = temp_string2.tenth_complement(temp_string2.string_number);
    }
    else if(num1.sign == '+' && num2.sign == '-')
    {
        //temp_string1.string_number STAY THE SAME.
        //temp_string1.string_number STAY THE SAME.
    }
    else
    {
        //temp_string1.string_number STAY THE SAME.
        temp_string2.string_number = temp_string2.tenth_complement(temp_string2.string_number);
    }
    sum.string_number = sum.add_two_string_numbers(temp_string1.string_number
                        , temp_string2.string_number);

     if (sum.sign == '-')
    {
        sum.string_number = sum.tenth_complement(sum.string_number);
    }
    return sum;
}
ostream& operator<<(ostream& out,const BigDecimalInt& big)          // ostream to display the output after doing the operators
{
    if(big.sign == '+')
    {
        out << big.string_number;
    }
    else
    {
        out << '-' << big.string_number;
    }
    return out;
}
