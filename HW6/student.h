/* Name: Forrest Lang
 * Date: 2 APR 2020
 * Section: 0005
 * Assignment: Homework 6
 * Due: 10 APR 2020
 */

#ifndef HW6_STUDENT_H
#define HW6_STUDENT_H

#include <iostream>

using namespace std;

/* ------------------------STUDENT BASE CLASS------------------------------- */

enum Subject {ENGLISH, HISTORY, MATH};

class Student {
    friend ostream& operator<<(ostream&, const Student&);
public:
    virtual double getGrade() const = 0;
    virtual int getFinal() const = 0;
    Subject getSubject() const;
    const char* getLast() const;
    const char* getFirst() const;

protected:
    char name_first[20];
    char name_last[20];
    Subject course;
};

/* ----------------------ENGLISH STUDENT CLASS------------------------------ */

class EnglishStudent : public Student {
public:
    EnglishStudent(const char* first, const char* last, int attendance,
                    int project, int midterm, int final);

    double getGrade() const;
    int getFinal() const;

private:
    // {Attendance: .1, Project: .3, Midterm: .3, Final Exam: .3}
    const double WEIGHTS[4];
    int assignments[4];
    const int NUM_ASSIGNMENTS;
};

/* ---------------------HISTORY STUDENT CLASS------------------------------- */

class HistoryStudent : public Student {
public:
    HistoryStudent(const char* first, const char* last, int paper, int midterm,
                    int final);

    double getGrade() const;
    int getFinal() const;

private:
    // {Term paper: .25, Midterm: .35, Final Exam: .4}
    const double WEIGHTS[3];
    int assignments[3];
    const int NUM_ASSIGNMENTS;
};

/* ---------------------MATH STUDENT CLASS---------------------------------- */

class MathStudent : public Student {
public:
    MathStudent(const char* first, const char* last, int q1, int q2, int q3,
                int q4, int q5, int t1, int t2, int final);

    double getGrade() const;
    int getFinal() const;

private:
    // {Quiz 1: .03, Quiz 2: .03, Quiz 3: .03, Quiz 4: .03, Quiz 5: .03,
    // Test 1: .25, Test 2: .25, Final: .35}
    const double WEIGHTS[8];
    int assignments[8];
    const int NUM_ASSIGNMENTS;
};

#endif //HW6_STUDENT_H
