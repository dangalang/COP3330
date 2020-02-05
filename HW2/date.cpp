/* Name: Forrest Lang
 * Date: 30 JAN 2020
 * Section: 0005
 * Assignment: Homework 2
 */

#include "date.h"
#include <iostream>
#include <iomanip>

// use cout.fill('0') for stuff

using namespace std;

Date::Date() {
    day = 1;
    month = 1;
    year = 2000;
    form = 'D';
}

Date::Date(int m, int d, int y) {
    if (IsValid(m, d, y)) {
        month = m;
        day = d;
        year = y;
    } else {
        month = 1;
        day = 1;
        year = 2000;
    }
    form = 'D';
}

void Date::Input() {
    int d, m, y;
    char temp;
    cout << "Enter date (mm/dd/yyyy): ";
    do {
        cin >> m >> temp >> d >> temp >> y;
        if (!Set(m, d, y))
            cout << "Invalid date. Try again: ";
    } while (!Set(m, d, y));
}

bool Date::Set(int m, int d, int y) {
    if (IsValid(m, d, y)) {
        month = m;
        day = d;
        year = y;
        return true;
    } else
        return false;
}

bool Date::SetFormat(char f) {
    switch (f) {
        case 'D':
            form = 'D';
            return true;
        case 'T':
            form = 'T';
            return true;
        case 'L':
            form = 'L';
            return true;
        case 'J':
            form = 'J';
            return true;
        default:
            return false;
    }

}

void Date::Increment(int numDays) {
    if (numDays < 1)
        return;
    while (day + numDays > DAYS_IN_MONTH[month - 1] + (month == 2 && IsLeap(year) ? 1 : 0)) {
        numDays -= DAYS_IN_MONTH[month - 1] + (month == 2 && IsLeap(year) ? 1 : 0) - day;
        day = 0;
        if (++month > 12) {
            month = 1;
            year++;
        }
    }
    day += numDays;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

int Date::GetYear() const {
    return year;
}

void Date::Show() const {
    int numDay = day;
    if (month > 2 && IsLeap(year)) numDay++;
    for (int i = 0; i < month - 1; i++)
        numDay += DAYS_IN_MONTH[i];

    switch (form) {
        case 'D':
            cout << month << '/' << day << '/' << year << endl;
            return;
        case 'T':
            cout << std::setfill('0') << std::setw(2) << month << '/';
            cout << std::setfill('0') << std::setw(2) << day << '/';
            cout << std::setfill('0') << std::setw(2) << year % 100 << endl;
            return;
        case 'L':
            cout << NAMES_OF_MONTH[month - 1] << ' ' << day << ", " << year << endl;
            return;
        case 'J':
            cout << std::setfill('0') << std::setw(2) << year % 100 << '-';
            cout << std::setfill('0') << std::setw(3) << numDay << endl;
            return;
        default:
            return;
    }
}

int Date::Compare(const Date &d) const {
    if (year < d.year) return -1;
    if (d.year < year) return 1;

    if (month < d.month) return -1;
    if (d.month < month) return 1;

    if (day < d.day) return -1;
    if (d.day < day) return 1;

    return 0;
}

bool Date::IsValid(int m, int d, int y) const {
    if (y < 0) return false;
    if (m > 12 || m < 1) return false;
    if (IsLeap(y) && m == 2 && d == 29) return true;
    if (d < 1 || d > DAYS_IN_MONTH[m - 1]) return false;

    return true;
}

bool Date::IsLeap(int y) const {
    if (y % 4 == 0) {
        if (y % 100 == 0 && y % 400 != 0) return false;
        return true;
    }
    return false;
}

const char *Date::NAMES_OF_MONTH[] =
        {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
const int Date::DAYS_IN_MONTH[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
