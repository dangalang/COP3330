/* Name: Forrest Lang
 * Date: 21 JAN 2020
 * Section: 0005
 * Assignment: Homework 1
 */

#include "house.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

House::House(int size, char wall, char fill) {
    // Verify size meets constraints or default to min/max
    if (size < 3) base = 3;
    else if (size > 37) base = 37;
    else base = size;

    // Use SetBorder and SetFill functions to check valid inputs.
    SetBorder(wall);
    SetFill(fill);
}

int House::GetSize() const {
    return base;
}

int House::Perimeter() const {
    int perimeter = 3 * base + 2 * (base + 2) + 2;
    return perimeter;
}

double House::Area() const {
    double area_base = pow(base, 2);
    double area_trig = sqrt(3) / 4 * pow(base + 2, 2);
    double area = area_base + area_trig;
    return area;
}

bool House::Grow() {
    if (base < 37) {
        base++;
        return true;
    } else {
        return false;
    }
}

bool House::Shrink() {
    if (base > 3) {
        base--;
        return true;
    } else {
        return false;
    }
}

bool House::SetBorder(char wall) {
    // must be valid ascii char
    if (wall >= 33 and wall <= 126) {  
        border = wall;
        return true;
    } else {
        border = 'X';
        return false;
    }
}

bool House::SetFill(char filler) {
    // must be valid ascii char
    if (filler >= 33 and filler <= 126) {  
        fill = filler;
        return true;
    } else {
        fill = '*';
        return false;
    }
}

void House::Draw() const {
    // print single roof peak
    for (int i = 0; i < base + 1; i++)
        cout << ' ';
    cout << border << endl;  

    // print bulk of the roof
    for (int i = 1; i < base + 1; i++) {
        for (int j = i; j < base + 1; j++)       // move over to center roof
            cout << ' ';
        cout << border;
        for (int j = 0; j < i * 2 - 1; j++)
            j % 2 ? cout << fill : cout << ' ';  // Draw fill every other space
        cout << border << endl;
    }

    // Draw the awkward intersect of the roof and base
    cout << border << ' ' << border << ' ';
    for (int i = 0; i < base - 2; i++)
        cout << fill << ' ';
    cout << border << ' ' << border << endl;

    // Draw the remainder of the base
    for (int i = 0; i < base - 2; i++) {
        cout << "  " << border << ' ';
        for (int j = 0; j < base - 2; j++)
            cout << fill << ' ';
        cout << border << endl;
    }
    cout << "  ";
    for (int i = 0; i < base; i++)
        cout << border << ' ';
    cout << endl;
}

void House::Summary() const {
    cout << "House width and height base to roof = " << base << " units." << endl;
    cout << "Perimeter of house = " << Perimeter() << " units." << endl;
    cout << fixed << setprecision(2);
    cout << "Area of house = " << Area() << " units." << endl;
    cout << "House looks like:" << endl;
    Draw();
}
