/* Name: Forrest Lang
 * Date: 2 APR 2020
 * Section: 0005
 * Assignment: Homework 6
 * Due: 10 APR 2020
 */

#ifndef HW6_STUDENTLIST_H
#define HW6_STUDENTLIST_H

#include "student.h"

class StudentList {
public:
    StudentList();
    ~StudentList();

    bool ImportFile(const char* filename);
    bool CreateReportFile(const char* filename);
    void ShowList() const;

private:
    void increaseSize(int num);
    void countGrades(ofstream& file_out, const char* letter, int lower,
            int upper) const;
    void showSubject(ofstream& file_out, const char* course_name,
            Subject subject) const;

    Student **stud_list;
    int num_studs;
};


#endif //HW6_STUDENTLIST_H
