/* Name: Forrest Lang
 * Date: 5 MAR 2020
 * Section: 0005
 * Assignment: Homework 5
 * Due: 26 MAR 2020
 */

#include "mystring.h"
#include <iostream>
#include <cstring>

using namespace std;

// ---------------------- MyString Friend functions ---------------------------

/* Operator overload for output stream.  Operator checks for null terminator
 * at the end of the string and if it does not exist, prints each character
 * one by one to prevent improper memory access. */
ostream& operator<<(ostream& os, const MyString& str) {
    if (str.data[str.length - 1] == '\0')
        os << str.data;
    else
        for (int i = 0; i < str.length; i++)
            os << str.data[i];
    return os;
}


/* Operator overload for input stream.  Operator accepts a whitespace limited
 * character string of various size by continually resizing the MyString
 * object based on the number of characters entered.  When a whitespace
 * character is detected, the string is resized to the appropriate number of
 * characters and a null terminator is added to the end. */
istream& operator>>(istream& is, MyString& str) {
    char next_char;
    int num = 0;
    str.resetArray(5);

    while (is.peek() == ' ' || is.peek() == '\n')
        is.get();
    while (is.peek() != ' ' && is.peek() != '\n') {
        is.get(next_char);
        if (str.length <= num) str.padArray(5);
        str.data[num++] = next_char;
    }
    if (str.length <= num) str.padArray(2);
    str.data[num] = '\0';
    str.trimArray();

    return is;
}


/* Geline function overload for istream objects.  For two parameter function
 * call, the character delimiter defaults to the newline character and the
 * three parameter function is called appropriately. */
istream& getline(istream& is, MyString& str) {
    return getline(is, str, '\n');
}


/* Geline function overload for istream objects.  Similarly to the insertion
 * operator overload, getline accepts a variable sized input and adjusts the
 * MyString object accordingly.  Rather than checking for a whitespace
 * character, getline accepts new characters until the chosen delimiter is
 * found. */
istream& getline(istream& is, MyString& str, char delim) {
    char next_char;
    int num = 0;
    str.resetArray(5);

    while (is.peek() != delim) {
        is.get(next_char);
        if (str.length <= num) str.padArray(5);
        str.data[num++] = next_char;
    }
    is.get();

    if (str.length <= num) str.padArray(2);
    str.data[num] = '\0';
    if (str.length != num)
        str.trimArray();

    return is;
}


/* Addition operator overload. The two MyString objects are concatenated and
 * a new MyString object is returned. */
MyString operator+(const MyString& str1, const MyString& str2) {
    MyString temp;
    temp.resetArray(str1.length + str2.length - 1);

    strcat(temp.data, str1.data);
    strcat(temp.data, str2.data);

    return temp;
}


/* Subtraction operator overload.  A new MyString object is returned in which
 * every instance of str2 is removed from str1. */
MyString operator-(const MyString& str1, const MyString& str2) {
    //TODO: Implement subtraction functionality
    MyString temp;

    return temp;
}


/* Less than comparison operator overload.  Returns true if str1 comes before
 * str2 lexicographically. */
bool operator<(const MyString& str1, const MyString& str2) {

    return strcmp(str1.data, str2.data) < 0;
}


/* Greater than comparison operator overload.  Returns true if str2 comes
 * before str1 lexicographically. */
bool operator>(const MyString& str1, const MyString& str2) {
    return str2 < str1;
}


/* Less than or equal to comparison operator overload.  Returns true if str2
 * comes before str1 or is identical to str1. */
bool operator<=(const MyString& str1, const MyString& str2) {
    if (!(str1 > str2)) return true;
    else return false;
}


/* Greater than or equal to comparison operator overload.  Returns true if
 * str1 comes before str2 or is identical to str2. */
bool operator>=(const MyString& str1, const MyString& str2) {
    return str2 <= str1;
}


/* Equality operator overload.  Returns true if the two strings are identical.*/
bool operator==(const MyString& str1, const MyString& str2) {
    return str1 <= str2 && str2 <= str1;
}


/* Inequality operator overload.  Returns true if the two strings are not
 * identical. */
bool operator!=(const MyString& str1, const MyString& str2) {
    return str1 < str2 || str2 < str1;
}


// ---------------------- MyString Public functions ---------------------------

/* Default constructor for MyString object.  Default object is a string of
 * one character length, containing only the null terminator. */
MyString::MyString() {
    length = 1;
    data = new char[length];
    data[0] = '\0';
}


/* Constructor for character array parameters.  Calculates the length of the
 * array and ensures the final character is the null terminator. */
MyString::MyString(const char* array) {
    length = strlen(array) + 1;
    data = new char[length];
    strcpy(data, array);
    data[length - 1] = '\0';
}


/* Constructor to convert from integer to MyString object. */
MyString::MyString(int num) {
    length = 1;
    int temp = num;
    while (temp != 0) {
        length++;
        temp /= 10;
    }
    data = new char[length];
    for (int i = length - 2; i >= 0; i--) {
        data[i] = num % 10 + '0';
        num /= 10;
    }
    data[length - 1] = '\0';
}


/* MyString object destructor used for cleaning up dynamic memory in data
 * array. */
MyString::~MyString() {
    delete [] data;
}


/* Copy constructor for MyString object. Creates a new MyString object of the
 * same length and copies the characters into a unique character array before
 * ensuring the final character is the null terminator. */
MyString::MyString(const MyString& str) {
    length = str.length;
    data = new char[length];
    strcpy(data, str.data);
    data[length - 1] = '\0';
}


/* Equality operator overload.  Resets the character array before copying the
 * other MyString data array into the local variable and forces the final
 * character to the null terminator. */
MyString& MyString::operator=(const MyString& str) {
    resetArray(str.length);
    strcpy(data, str.data);
    data[length - 1] = '\0';
}


/* Addition equality operator overload.  Leverages the addition operator
 * overload to concatenate the R-value string with the L-value MyString
 * object. */
MyString& MyString::operator+=(const MyString& str) {
    MyString temp = *this + str;
    resetArray(temp.length);
    strcpy(data, temp.data);
}


/* Bracket operator overload.  Allows for modification of the MyString
 * characters.  If an index greater than the string length is requested, the
 * string will be extended to the necessary length with whitespace. */
char& MyString::operator[](unsigned int index) {
    if (index < length) return data[index];
    else {
        int padding = index - length;
        char * temp = new char[padding + 2];
        for (int i = 0; i <= padding; i++) temp[i] = ' ';
        temp[padding + 1] = '\0';

        *this += temp;
        delete [] temp;
        return data[index];
    }
}


/* Bracket operator overload for constant objects.  Allows for access but not
 * modification of MyString object characters.  If the requested index is
 * greater than the string length, the null terminator is returned. */
const char& MyString::operator[](unsigned int index) const {
    if (index < length) return data[index];
    else return data[length - 1];
}


/* Insertion function for MyString objects allows for a substring to be
 * inserted at any point in the string.  If the index is greater than the
 * original string's length, the substring is placed at the end. */
MyString& MyString::insert(unsigned int index, const MyString &s) {
    if (index < length) {
        char * temp = new char[length + s.length];
        for (int i = 0; i < index; i++) temp[i] = data[i];
        for (int i = 0; i < s.getLength(); i++) temp[index + i] = s[i];
        for (int i = index; i < length; i++)
            temp[i + s.length - 1] = data[i];
        temp[length + s.length - 1] = '\0';

        *this = temp;
        delete [] temp;
    } else *this += s;

    return *this;
}


/* Scans the MyString object for the provided substring and returns its index.
 *  If no substring is found, -1 is returned instead. */
int MyString::indexOf(const MyString &s) const {
    int location = static_cast<int>(strstr(data, s.data) - data);
    if (location < *data + length && location > 0)
        return location;
    else
        return -1;
}


/* Returns the number of characters in the MyString object.  The null
 * terminator is not included in this total. */
int MyString::getLength() const {
    return length - 1;
}


/* Returns the character array of the MyString object. */
const char* MyString::getCString() const {
    return data;
}


/* Returns a substring of the MyString object when provided the initial
 * starting index and substring length.  If the starting position is greater
 * than the string length, an empty string is returned. */
MyString MyString::substring(unsigned int start, unsigned int num) const {
    if (start >= length) return MyString();
    if (start + num < length) {
        char temp[start + num + 1];
        strncpy(temp, data + start, start + num);
        temp[num] = '\0';
        return MyString(temp);

    } else return substring(start);
}


/* Returns the substring of the MyString object starting at the provided
 * index and ending at the null terminator.  If the starting position is
 * greater than the string length, an empty string is returned. */
MyString MyString::substring(unsigned int start) const {
    if (start >= length) return MyString();
    else {
        char temp[length - start + 1];
        strcpy(temp, data + start);
        temp[length - start] = '\0';

        return MyString(temp);
    }
}


// ---------------------- MyString Private functions --------------------------

/* Dynamic memory handling function deletes the old character array and
 * creates a new one with the provided size. */
void MyString::resetArray(int size) {
    delete [] data;
    length = size;
    data = new char[length];
}


/* Helper function used to increase the size of the string length while
 * preserving currently recorded characters. */
void MyString::padArray(int padding) {
    int old_length = length;
    char temp[old_length];
    strncpy(temp, data, old_length);
    resetArray(old_length + padding);
    strncpy(data, temp, old_length);
    data[old_length] = '\0';
}


/* Helper function used to decrease the size of the string to the minimum
 * required amount while preserving the string itself and ensure a
 * terminating null character. */
void MyString::trimArray() {
    int str_length = strlen(data) + 1;
    char temp[str_length];
    strncpy(temp, data, str_length);
    resetArray(str_length);
    strncpy(data, temp, length);
    data[length - 1] = '\0';
}
