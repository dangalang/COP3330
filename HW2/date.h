/* Name: Forrest Lang
 * Date: 30 JAN 2020
 * Section: 0005
 * Assignment: Homework 2
 */

class Date {
public:
    // Constructors
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

    int Compare(const Date &d) const;

private:
    // Given a date, check if it is older than 0 CE/AD, a month between 1 and
    // 12, and if it is a leap year that the days fall within the monthly range
    bool IsValid(int m, int d, int y) const;

    // Check if the year is a multiple of 4 and if that year is a centenial,
    // if it is also a multiple of 400
    bool IsLeap(int y) const;

    int month;
    int day;
    int year;
    enum Form {
        Default, TwoDigit, LongForm, Julian
    };
    Form form;

    // Names of the month used for printing the long date format
    static const char *NAMES_OF_MONTH[12];

    // Days in each month, used for calculating date validity, monthly
    // increments and julian dates
    static const int DAYS_IN_MONTH[12];
};
