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
    os << str.data;
    return os;
}


istream& operator>>(istream& is, MyString& str) {
    is >> str.data;
    return is;
}


istream& getline(istream& is, MyString& str) {
    is.getline(str.data);
    return is;
}


istream& getline(istream& is, MyString& str, char delim) {
    is.getline(str.data, delim);
    return is;
}


MyString operator+(const MyString& str1, const MyString& str2) {
    return MyString(strcat(str1.data, str2.data));
}


MyString operator-(const MyString& str1, const MyString& str2) {
    MyString temp;

    return temp;
}


bool operator<(const MyString& str1, const MyString& str2) {

    return strcmp(str1, str2);
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

MyString::MyString() {
    length = 1;
    data = new char[length];
    data[0] = '\0';
}


MyString::MyString(const char* array) {
    length = strlen(array) + 1;
    data = new char[length];
    strcpy(data, array);
    data[length - 1] = '\0';
}


MyString::MyString(int num) {
    length = num / 10 + 2;
    data = new char[length];
    for (int i = 0; i < length; i++) {
        data[length - 1 - i] = num % 10;
        num /= 10;
    }
    data[length - 1] = '\0';
}


MyString::~MyString() {
    delete [] data;
}


MyString::MyString(const MyString& str) {
    length = str.length;
    data = new char[length];
    strcpy(data, str.data);
    data[length - 1] = '\0';
}


MyString& MyString::operator=(const MyString& str) {
    delete [] data;
    length = str.length;
    data = new char[length];
    strcpy(data, str.data);
    data[length - 1] = '\0';
}


MyString& MyString::operator+=(const MyString& str) {
    temp = *this + str;
    delete [] data;
    length = temp.length();
    data = new char[length];
    strcpy(data, temp.data);
}

char& MyString::operator[](unsigned int index) {
    if (index < length) return &data[index];
    else return data[length - 1];
}


const char& MyString::operator[](unsigned int index) const {
    if (index < length) return &data[index];
    else return &data[length - 1];
}


MyString& MyString::insert(unsigned int index, const MyString &s) {
    if (index < length) {
        char temp[length + s.length];
        for (int i = 0; i < index; i++) temp[i] = data[i];
        for (int i = 0; i < s.getLength(); i++) temp[index + i] = s[i];
        for (int i = index; i < length; i++) temp[i] = data[i - index];
        data[length - 1] = '\0';
    } else *this += s;

    return *this;
}


int MyString::indexOf(const MyString &s) const {
    return strstr(data, s.data);
}


int MyString::getLength() const {
    return length - 1;
}


const char* MyString::getCString() const {
    return data;
}


MyString MyString::substring(unsigned int start, unsigned int end) const {
    if (start > end || start >= length) return MyString();
    if (end < length) {
        char temp[end - start + 1];
        strncpy(temp, data + start, end);
        temp[end - start] = '\0';
        return MyString(temp);

    } else return substring(start);
}


MyString MyString::substring(unsigned int start) const {
    if (start >= length) return MyString();
    else {
        char temp[length - start + 1];
        strncpy(temp, data + start);
        temp[length - start] = '\0';

        return MyString(temp);
    }
}
