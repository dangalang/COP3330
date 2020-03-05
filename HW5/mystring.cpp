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
    //TODO: Don't do this. must allow variable number of characters
    is >> str.data;
    return is;
}


istream& getline(istream& is, MyString& str) {
    return getline(is, str, '\n');
}


istream& getline(istream& is, MyString& str, char delim) {
    //TODO: Don't do this. must allow any number of characters
    char temp[256];
    is.getline(temp, 256, delim);
    delete [] str.data;
    str.length = strlen(temp) + 1;
    str.data = new char[str.length];
    for (int i = 0; i < str.length; i++) {
        str.data[i] = temp[i];
    }
    str.data[str.length - 1] = '\0';
    return is;
}


MyString operator+(const MyString& str1, const MyString& str2) {
    MyString temp;
    temp.length = str1.length + str2.length - 1;
    delete [] temp.data;
    temp.data = new char[temp.length];

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
    length = 1;
    int temp = num;
    while (temp != 0) {
        length++;
        temp /= 10;
    }
    data = new char[length];
    for (int i = 0; i < length; i++) {
        data[length - 2 - i] = num % 10 + '0';
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
    MyString temp = *this + str;
    delete [] data;
    length = temp.length;
    data = new char[length];
    strcpy(data, temp.data);
}

char& MyString::operator[](unsigned int index) {
    //TODO: Resize string to new index length and fill with spaces
    if (index < length) return data[index];
    else return data[length - 1];
}


const char& MyString::operator[](unsigned int index) const {
    if (index < length) return data[index];
    else return data[length - 1];
}


MyString& MyString::insert(unsigned int index, const MyString &s) {
    //TODO: Fix broken insertion
    if (index < length) {
        char temp[length + s.length];
        for (int i = 0; i < index; i++) temp[i] = data[i];
        for (int i = 0; i < s.getLength(); i++) temp[index + i] = s[i];
        for (int i = index; i < length; i++)
            temp[i + length] = data[i];
        data[length - 1] = '\0';
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
