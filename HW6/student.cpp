/* Name: Forrest Lang
 * Date: 2 APR 2020
 * Section: 0005
 * Assignment: Homework 6
 * Due: 10 APR 2020
 */

#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

/* ------------------------STUDENT BASE CLASS------------------------------- */

/* Output stream operator overload for Student classes.  Name and grades are
 * formatted to align nicely with the StudentList.CreateReportFile function. */
ostream& operator<<(ostream& os, const Student& stud) {
    double grade = stud.getGrade();

    ios_base::fmtflags old_flags = os.flags();
    int old_precision = os.precision();
    os << left;

    os << stud.getFirst() << " ";
    os.width(41 - strlen(stud.getFirst()));
    os << stud.getLast();

    os.width(6);
    os << stud.getFinal();

    os.width(8);
    os << fixed;
    os.precision(2);
    os << grade;

    if (grade < 60) os << 'F';
    else if (grade < 70) os << 'D';
    else if (grade < 80) os << 'C';
    else if (grade < 90) os << 'B';
    else os << 'A';

    os << endl;

    os.flags(old_flags);
    os.precision(old_precision);
}


Subject Student::getSubject() const {
    return course;
}


const char* Student::getLast() const {
    return name_last;
}


const char* Student::getFirst() const {
    return name_first;
}


/* ----------------------ENGLISH STUDENT CLASS------------------------------ */

/* English Student constructor. Receives name and grades as parameters.
 * Assignment weights are fixed and passed as constants to the constructor
 * along with the total number of assignments.  These constant values are
 * used for computing final grades. */
EnglishStudent::EnglishStudent(const char* first, const char* last,
        int attendance, int project, int midterm, int final) :
        NUM_ASSIGNMENTS(4), WEIGHTS{.1, .3, .3, .3} {
    strncpy(name_first, first, 20);
    strncpy(name_last, last, 20);
    assignments[0] = attendance;
    assignments[1] = project;
    assignments[2] = midterm;
    assignments[3] = final;
    course = ENGLISH;
}


/* Compute Student's final grade by multiplying each assignment score by the
 * assignment weight and sum the results. */
double EnglishStudent::getGrade() const {
    double average = 0;
    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        average += assignments[i] * WEIGHTS[i];
    return average;
}


/* Return the score received on the Final Exam. */
int EnglishStudent::getFinal() const {
    return assignments[NUM_ASSIGNMENTS - 1];
}

/* ---------------------HISTORY STUDENT CLASS------------------------------- */

/* History Student constructor. Receives name and grades as parameters.
 * Assignment weights are fixed and passed as constants to the constructor
 * along with the total number of assignments.  These constant values are
 * used for computing final grades. */
HistoryStudent::HistoryStudent(const char *first, const char *last, int paper,
        int midterm, int final)
        : NUM_ASSIGNMENTS(3), WEIGHTS{.25, .35, .4} {
    strncpy(name_first, first, 20);
    strncpy(name_last, last, 20);
    assignments[0] = paper;
    assignments[1] = midterm;
    assignments[2] = final;
    course = HISTORY;
}


/* Compute Student's final grae by multiplying each assignment score by the
 * assignment's weight and sum the results. */
double HistoryStudent::getGrade() const {
    double average = 0;
    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        average += assignments[i] * WEIGHTS[i];
    return average;
}


/* Return the score received on the Final Exam. */
int HistoryStudent::getFinal() const {
    return assignments[NUM_ASSIGNMENTS - 1];
}

/* ---------------------MATH STUDENT CLASS---------------------------------- */

/* Math Student constructor. Receives name and grades as parameters.
 * Assignment weights are fixed and passed as constants to the constructor
 * along with the total number of assignments.  These constant values are
 * used for computing final grades. */
MathStudent::MathStudent(const char *first, const char *last, int q1, int q2,
        int q3, int q4, int q5, int t1, int t2, int final)
        : NUM_ASSIGNMENTS(8),
          WEIGHTS{.03, .03, .03, .03, .03, .25, .25, .35} {
    strncpy(name_first, first, 20);
    strncpy(name_last, last, 20);
    assignments[0] = q1;
    assignments[1] = q2;
    assignments[2] = q3;
    assignments[3] = q4;
    assignments[4] = q5;
    assignments[5] = t1;
    assignments[6] = t2;
    assignments[7] = final;
    course = MATH;
}


/* Compute Student's final grae by multiplying each assignment score by the
 * assignment's weight and sum the results. To account for quiz grade average
 * totaling 15% of final grade, each quiz is worth 3% of final grade. */
double MathStudent::getGrade() const {
    double average = 0;
    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        average += assignments[i] * WEIGHTS[i];
    return average;
}


/* Return the score received on the Final Exam. */
int MathStudent::getFinal() const {
    return assignments[NUM_ASSIGNMENTS - 1];
}