/* Name: Forrest Lang
 * Date: 10 FEB 2020
 * Section: 0005
 * Assignment: Homework 3
 */

#include <iostream>
#include "distance.h"

using namespace std;

// FRIEND FUNCTIONS

//TODO: Is it better to comment functions in .h or .cpp

/* OStream overload for Distance objects (MILESm YARDSy FEET' INCHES").  Inches
 * will always be displayed but miles, yards and feet will only display if
 * nonzero. */
ostream& operator<<(ostream& s, const Distance& d) {
    if (d.GetMiles()) s << d.GetMiles() << "m ";
    if (d.GetYards()) s << d.GetYards() << "y ";
    if (d.GetFeet())  s << d.GetFeet()  << "\' ";
    s << d.GetInches() << '\"';

    return s;
}


/* IStream overload for Distance objects (format: MILES,YARDS,FEET,INCHES).
 * Values are entered in a comma separated list and only positive distances
 * are accepted.  If values are not fully simplified, it will be done
 * automatically. */
istream& operator>>(istream& s, Distance& d) {
    char comma;
    int mi, yd, ft, in;

    s >> mi >> comma >> yd >> comma >> ft >> comma >> in;
    d = Distance(mi, yd, ft, in);

    return s;
}


// Addition operator overload for Distance objects
Distance operator+(const Distance& d1, const Distance& d2) {
    int mi = d1.GetMiles()  + d2.GetMiles();
    int yd = d1.GetYards()  + d2.GetYards();
    int ft = d1.GetFeet()   + d2.GetFeet();
    int in = d1.GetInches() + d2.GetInches();

    //TODO: What is list/aggregate initialization
    return Distance(mi, yd, ft, in);
}


/* Subtraction operator overload for Distance objects.  If result is a
 * negative value, distance will default to zero. */
Distance operator-(const Distance& d1, const Distance& d2) {
    int mi = d1.GetMiles()  - d2.GetMiles();
    int yd = d1.GetYards()  - d2.GetYards();
    int ft = d1.GetFeet()   - d2.GetFeet();
    int in = d1.GetInches() - d2.GetInches();

    if (in < 0) {
        ft--;
        in += Distance::INCHES_PER_FOOT;
    } if (ft < 0) {
        yd--;
        ft += Distance::FEET_PER_YARD;
    } if (yd < 0) {
        mi--;
        yd += Distance::YARDS_PER_MILE;
    }

    return Distance(mi, yd, ft, in);
}


/* Multiplication operator overload for distance object.  Distances can only
 * be multiplied by an integer.  Any negative multiple will default to zero. */
Distance operator*(const Distance& d1, int mult) {
    int mi, yd, ft, in;
    mi = d1.GetMiles()  * mult;
    yd = d1.GetYards()  * mult;
    ft = d1.GetFeet()   * mult;
    in = d1.GetInches() * mult;

    return Distance(mi, yd, ft, in);
}


// Less than operator overload for Distance objects.
bool operator<(const Distance& d1, const Distance& d2) {
    if (d1.GetMiles()  < d2.GetMiles())  return true;
    if (d1.GetYards()  < d2.GetYards())  return true;
    if (d1.GetFeet()   < d2.GetFeet())   return true;
    if (d1.GetInches() < d2.GetInches()) return true;
    return false;
}


// Greater than operator overload for Distance objects.
bool operator>(const Distance& d1, const Distance& d2) {
    return d2 < d1;
}


// Less than or equal to operator overload for Distance objects.
bool operator<=(const Distance& d1, const Distance& d2) {
    if (!(d1 > d2)) return true;
    else return false;
}


// Greater than or equal to operator overload for Distance objects.
bool operator>=(const Distance& d1, const Distance& d2) {
    return d2 <= d1;
}


// Equality operator overload for Distance objects.
bool operator==(const Distance& d1, const Distance& d2) {
    return d1 <= d2 && d1 >= d2;
}


// Inequality operator overload for Distance objects.
bool operator!=(const Distance& d1, const Distance& d2) {
    return d1 < d2 || d1 > d2;
}


// MEMBER FUNCTIONS

// Distance objects default to 0m 0y 0' 0"
Distance::Distance() {
    inches = 0;
    feet = 0;
    yards = 0;
    miles = 0;
}


/* Create a Distance object with an inches input parameter.  First set object's
 * distance to zero before checking for positivity and simplifying.  This
 * avoids bugs with random memory locations when assigning new objects to
 * typecasted integers (eg. Distance d = 52;) */
Distance::Distance(int in) {
    inches = 0;
    feet = 0;
    yards = 0;
    miles = 0;
    if (in > 0) {
        inches = in;
        simplify(*this);
    }
}


/* Create a Distance object with parameterized miles, yards, feet and inches.
 * Check for valid distance values before assignment and simplification.  If
 * values are not valid, default to a zero distance. */
Distance::Distance(int mi, int yd, int ft, int in) {
    if (mi >= 0 && yd >= 0 && ft >= 0 && in >= 0) {
        inches = in;
        feet = ft;
        yards = yd;
        miles = mi;
        simplify(*this);
    } else {
        inches = 0;
        feet = 0;
        yards = 0;
        miles = 0;
    }
}

//TODO: Returning non-constant objects vs. constant object types

// post-fix incrementation of Distance objects increases distance by one inch.
Distance Distance::operator++(int) {
    Distance temp = *this;
    inches++;
    simplify(*this);

    return temp;
}


Distance& Distance::operator++() {
    (*this)++;
    return *this;
}


/* Post-fix decrementation of Distance objects decreases distance by one inch.
 * If a non-zero distance is simplified to zero inches (or inches and feet,
 * etc.) decrement the next smallest non-zero unit and add the appropriate
 * amount of inches back in before simplifying again. */
Distance Distance::operator--(int) {
    Distance temp = *this;

    if (inches > 0) inches--;
    else {
        if (feet > 0) {
            feet--;
            inches += INCHES_PER_FOOT - 1;
        } else if (yards > 0) {
            yards--;
            inches += FEET_PER_YARD * INCHES_PER_FOOT - 1;
            simplify(*this);
        } else if (miles > 0) {
            miles--;
            inches += YARDS_PER_MILE * FEET_PER_YARD * INCHES_PER_FOOT - 1;
            simplify(*this);
        }
    }

    return temp;
}


Distance& Distance::operator--() {
    (*this)--;
    return *this;
}


/* Simplify the distance values to the smallest unit values.  By starting at
 * inches the function increments the feet by finding how many whole feet can
 * be made with available inches then sets the inches to the leftover amount
 * before repeating the procedure on feet then yards. */
void Distance::simplify(Distance &d1) {
    if (d1.inches >= INCHES_PER_FOOT) {
        d1.feet += d1.inches / INCHES_PER_FOOT;
        d1.inches %= INCHES_PER_FOOT;
    }
    if (d1.feet >= FEET_PER_YARD) {
        d1.yards += d1.feet / FEET_PER_YARD;
        d1.feet %= FEET_PER_YARD;
    }
    if (d1.yards >= YARDS_PER_MILE) {
        d1.miles += d1.yards / YARDS_PER_MILE;
        d1.yards %= YARDS_PER_MILE;
    }
}


int Distance::GetMiles() const {
    return miles;
}


int Distance::GetYards() const {
    return yards;
}


int Distance::GetFeet() const {
    return feet;
}


int Distance::GetInches() const {
    return inches;
}


// Constants used for quick algebra and readability
const int Distance::INCHES_PER_FOOT = 12;
const int Distance::FEET_PER_YARD = 3;
const int Distance::YARDS_PER_MILE = 1760;

