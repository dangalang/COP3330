/* Name: Forrest Lang
 * Date: 30 JAN 2020
 * Section: 0005
 * Assignment: Homework 2
 */

#include "date.h"
#include <iostream>
#include <iomanip>

using namespace std;

Date::Date() {
    day = 1;
    month = 1;
    year = 2000;
    form = Default;
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
    form = Default;
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
        case 'D':        // Default format, M/D/Y
            form = Default;
            return true;
        case 'T':        // Two-Digit format, mm/dd/yy
            form = TwoDigit;
            return true;
        case 'L':        // Long format, month D, Y
            form = LongForm;
            return true;
        case 'J':        // Julian format, YY-JJJ
            form = Julian;
            return true;
        default:
            return false;
    }

}

void Date::Increment(int numDays) {
    if (numDays < 1)
        return;
    // check if the number of days will move into the next month
    while (day + numDays > DAYS_IN_MONTH[month - 1] +
                           (month == 2 && IsLeap(year) ? 1 : 0)) {
        // remove the number of days required to get to the next month
        numDays -= DAYS_IN_MONTH[month - 1] +
                   (month == 2 && IsLeap(year) ? 1 : 0) - day;
        day = 0;
        if (++month > 12) {
            month = 1;
            year++;
        }
    }
    // the remaining days will be the current day of the month
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
    // calculate julian day by summing previous months
    int numDay = day;
    if (month > 2 && IsLeap(year)) numDay++;
    for (int i = 0; i < month - 1; i++)
        numDay += DAYS_IN_MONTH[i];

    switch (form) {
        case Default:        // Default format: M/D/Y
            cout << month << '/' << day << '/' << year << endl;
            return;
        case TwoDigit:        // Two Digit format: mm/dd/yy
            cout << std::setfill('0') << std::setw(2) << month << '/';
            cout << std::setfill('0') << std::setw(2) << day << '/';
            cout << std::setfill('0') << std::setw(2) << year % 100 << endl;
            return;
        case LongForm:        // Long format: month D, Y
            cout << NAMES_OF_MONTH[month - 1] << ' ' << day << ", " << year << endl;
            return;
        case Julian:        // Julian format: YY-JJJ
            cout << std::setfill('0') << std::setw(2) << year % 100 << '-';
            cout << std::setfill('0') << std::setw(3) << numDay << endl;
            return;
        default:
            return;
    }
}

int Date::Compare(const Date &d) const {
    // check which year comes first
    if (year < d.year) return -1;
    if (d.year < year) return 1;

    // assuming years are equal, check which month comes first
    if (month < d.month) return -1;
    if (d.month < month) return 1;

    // assuming months are equal, check which day comes first
    if (day < d.day) return -1;
    if (d.day < day) return 1;

    // can confidently say the dates are equal
    return 0;
}

bool Date::IsValid(int m, int d, int y) const {
    // no years prior to 0 CE/AD
    if (y < 0) return false;
    if (m > 12 || m < 1) return false;
    // check if date is specifically 29 feb
    if (IsLeap(y) && m == 2 && d == 29) return true;
    if (d < 1 || d > DAYS_IN_MONTH[m - 1]) return false;

    return true;
}

bool Date::IsLeap(int y) const {
    if (y % 4 == 0) {
        // If year is multiple of 4, check if centenial and multiple of 400
        if (y % 100 == 0 && y % 400 != 0) return false;
        return true;
    }
    return false;
}

const char *Date::NAMES_OF_MONTH[] =
        {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sept",
         "Oct", "Nov", "Dec"};
const int Date::DAYS_IN_MONTH[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
