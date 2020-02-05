/* Name: Forrest Lang
 * Date: 30 JAN 2020
 * Section: 0005
 * Assignment: Homework 2
 */

class Date {
public:
    Date();
    Date(int m, int d, int y);

    // Mutators:
    void Input();
    bool Set(int m, int d, int y);
    bool SetFormat(char f);
    void Increment(int numDays = 1);

    // Accessors:
    int GetMonth() const;
    int GetDay() const;
    int GetYear() const;
    void Show() const;
    int Compare(const Date& d) const;

private:
    bool IsValid(int m, int d, int y) const;
    bool IsLeap(int y) const;

    int month;
    int day;
    int year;
    char form;

    static const char * NAMES_OF_MONTH[12];
//            {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};
    static const int DAYS_IN_MONTH[12];
//        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};
