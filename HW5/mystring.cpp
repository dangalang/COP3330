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

ostream& operator<<(ostream& os, const MyString& str) {
    if (str.data[str.length - 1] == '\0')
        os << str.data;
    else
        for (int i = 0; i < str.length; i++)
            os << str.data[i];
    return os;
}


istream& operator>>(istream& is, MyString& str) {
    char next_char;
    int num = 0;
    str.resetArray(5);

    while (is.peek() == ' ')
        is.get();
    while (is.peek() != ' ') {
        is.get(next_char);
        if (str.length <= num) str.padArray(5);
        str.data[num++] = next_char;
    }
    if (str.length <= num) str.padArray(2);
    str.data[num] = '\0';
    str.trimArray();

    return is;
}


istream& getline(istream& is, MyString& str) {
    return getline(is, str, '\n');
}


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


MyString operator+(const MyString& str1, const MyString& str2) {
    MyString temp;
    temp.resetArray(str1.length + str2.length - 1);

    strcat(temp.data, str1.data);
    strcat(temp.data, str2.data);

    return temp;
}


MyString operator-(const MyString& str1, const MyString& str2) {
    MyString temp;

    return temp;
}


bool operator<(const MyString& str1, const MyString& str2) {

    return strcmp(str1.data, str2.data) < 0;
}


bool operator>(const MyString& str1, const MyString& str2) {
    return str2 < str1;
}


bool operator<=(const MyString& str1, const MyString& str2) {
    if (!(str1 > str2)) return true;
    else return false;
}


bool operator>=(const MyString& str1, const MyString& str2) {
    return str2 <= str1;
}


bool operator==(const MyString& str1, const MyString& str2) {
    return str1 <= str2 && str2 <= str1;
}


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


MyString& MyString::operator+=(const MyString& str) {
    MyString temp = *this + str;
    resetArray(temp.length);
    strcpy(data, temp.data);
}

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


const char& MyString::operator[](unsigned int index) const {
    if (index < length) return data[index];
    else return data[length - 1];
}


MyString& MyString::insert(unsigned int index, const MyString &s) {
    //TODO: Fix broken insertion
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


int MyString::indexOf(const MyString &s) const {
    int location = static_cast<int>(strstr(data, s.data) - data);
    if (location < *data + length && location > 0)
        return location;
    else
        return -1;
}


int MyString::getLength() const {
    return length - 1;
}


const char* MyString::getCString() const {
    return data;
}


MyString MyString::substring(unsigned int start, unsigned int num) const {
    if (start >= length) return MyString();
    if (start + num < length) {
        char temp[start + num + 1];
        strncpy(temp, data + start, start + num);
        temp[num] = '\0';
        return MyString(temp);

    } else return substring(start);
}


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


void MyString::resetArray(int size) {
    delete [] data;
    length = size;
    data = new char[length];
}


void MyString::padArray(int padding) {
    int old_length = length;
    char temp[old_length];
    strncpy(temp, data, old_length);
    resetArray(old_length + padding);
    strncpy(data, temp, old_length);
    data[old_length] = '\0';
}


void MyString::trimArray() {
    int str_length = strlen(data) + 1;
    char temp[str_length];
    strncpy(temp, data, str_length);
    resetArray(str_length);
    strncpy(data, temp, length);
    data[length - 1] = '\0';
}
