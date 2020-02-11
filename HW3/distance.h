/* Name: Forrest Lang
 * Date: 10 FEB 2020
 * Section: 0005
 * Assignment: Homework 3
 */

using namespace std;

class Distance {

    friend ostream& operator<<(ostream& s, const Distance& d);
    friend istream& operator>>(istream& s, Distance& d);

    friend Distance operator+(const Distance& d1, const Distance& d2);
    friend Distance operator-(const Distance& d1, const Distance& d2);
    friend Distance operator*(const Distance& d1, const Distance& d2);

    friend bool operator<(const Distance& d1, const Distance& d2);
    friend bool operator>(const Distance& d1, const Distance& d2);
    friend bool operator<=(const Distance& d1, const Distance& d2);
    friend bool operator>=(const Distance& d1, const Distance& d2);
    friend bool operator==(const Distance& d1, const Distance& d2);
    friend bool operator!=(const Distance& d1, const Distance& d2);


public:
    Distance();
    Distance(int in);
    Distance(int mi, int yd, int ft, int in);

    Distance& operator++();
    Distance operator++(int);
    Distance& operator--();
    Distance operator--(int);

    int GetMiles() const;
    int GetYards() const;
    int GetFeet() const;
    int GetInches() const;

private:
    void simplify(Distance& d1);

    int miles, yards, feet, inches;

    static const int INCHES_PER_FOOT;
    static const int FEET_PER_YARD;
    static const int YARDS_PER_MILE;
};
