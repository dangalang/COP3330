/* Name: Forrest Lang
 * Date: 2 APR 2020
 * Section: 0005
 * Assignment: Homework 6
 * Due: 10 APR 2020
 */

#include <cstring>
#include <fstream>

#include "StudentList.h"
#include "student.h"

/* Student List constructor for creating an empty list. */
StudentList::StudentList() {
    num_studs = 0;
    stud_list = new Student*[num_studs];
}


/* Student List destructor for cleaning up dynamic memory. */
StudentList::~StudentList() {
    for (int i = 0; i < num_studs; i++)
        delete stud_list[i];
    delete [] stud_list;
}


/* Import students from file.  Student list is dynamically resized to
 * accomodate incoming students and grades.  Names and values are stored
 * before checking student major and calling appropriate student constructor.
 * Students are stored in the order they are received and duplicate students
 * may be stored in the same list. */
bool StudentList::ImportFile(const char* filename) {
    ifstream file_in;
    int new_studs;
    char first_name[20], last_name[20], major[8];
    int assignments[8];
    Subject subject;

    file_in.open(filename);
    if (!file_in) return false;

    file_in >> new_studs;
    file_in.get();
    increaseSize(new_studs);

    for (int i = 0; i < new_studs; i++) {
        file_in.getline(last_name, 20, ',');
        file_in.get();
        file_in.getline(first_name, 20);
        file_in >> major;

        if (strncmp(major, "English", 8) == 0) subject = ENGLISH;
        else if (strncmp(major, "History", 8) == 0) subject = HISTORY;
        else if (strncmp(major, "Math", 5) == 0) subject = MATH;

        switch (subject) {
            case ENGLISH:
                for (int j = 0; j < 4; j++)
                    file_in >> assignments[j];
                stud_list[num_studs++] = new EnglishStudent(first_name,
                        last_name, assignments[0], assignments[1],
                        assignments[2], assignments[3]);
                break;
            case HISTORY:
                for (int j = 0; j < 3; j++)
                    file_in >> assignments[j];
                stud_list[num_studs++] = new HistoryStudent(first_name,
                        last_name, assignments[0], assignments[1],
                        assignments[2]);
                break;
            case MATH:
                for (int j = 0; j < 8; j++)
                    file_in >> assignments[j];
                stud_list[num_studs++] = new MathStudent(first_name, last_name,
                        assignments[0], assignments[1], assignments[2],
                        assignments[3], assignments[4], assignments[5],
                        assignments[6], assignments[7]);
                break;
            default:
                break;
        }
        file_in.get();                  // Get rid of newline after grades
    }

    file_in.close();
    return true;
}


/* Create a file output report containing formatted student breakdown.
 * Students are organized into major in the order they are imported into the
 * list and the overall grade distribution is included at the end. */
bool StudentList::CreateReportFile(const char* filename) {
    ofstream file_out;

    file_out.open(filename);
    if (!file_out) return false;

    file_out << "Student Grade Summary\n---------------------\n\n";
    showSubject(file_out, "ENGLISH", ENGLISH);
    showSubject(file_out, "HISTORY", HISTORY);
    showSubject(file_out, "MATH", MATH);

    file_out << "OVERALL GRADE DISTRIBUTION\n\n";
    countGrades(file_out, "A", 90, 100);
    countGrades(file_out, "B", 80, 90);
    countGrades(file_out, "C", 70, 80);
    countGrades(file_out, "D", 60, 70);
    countGrades(file_out, "F", 0, 60);

    file_out.close();
    return true;
}


/* Brief student output to console.  Shows student names and subject in the
 * order they are imported. */
void StudentList::ShowList() const {
    ios_base::fmtflags old_flags = cout.flags();
    int old_precision = cout.precision();

    cout.width(21);
    cout << left;
    cout << "Last";

    cout.width(21);
    cout << "First";

    cout << "Course\n\n";
    for (int i = 0; i < num_studs; i++) {
        cout.width(21);
        cout << stud_list[i]->getLast();

        cout.width(21);
        cout << stud_list[i]->getFirst();
        if (stud_list[i]->getSubject() == ENGLISH)
            cout << "ENGLISH";
        if (stud_list[i]->getSubject() == HISTORY)
            cout << "HISTORY";
        if (stud_list[i]->getSubject() == MATH)
            cout << "MATH";
        cout << endl;
    }

    cout.flags(old_flags);
    cout.precision(old_precision);
}


/* Memory helper function used to increase the size of the student list by
 * the appropriate amount. */
void StudentList::increaseSize(int num) {
    Student ** temp = new Student*[num_studs + num];
    for (int i = 0; i < num_studs; i++)
        temp[i] = stud_list[i];

    delete [] stud_list;
    stud_list = temp;
}


/* Helper function used to calculate the number of students who scored within
 * a desired range.  The desired letter grade is passed in along with the
 * grading limits and the number of students falling within that range is
 * computed and output to the stream. */
void StudentList::countGrades(ofstream& file_out, const char* letter, int lower,
        int upper) const {
    int num_grade = 0;

    file_out << letter << ":";
    for (int i = 0; i < num_studs; i++) {
        if (stud_list[i]->getGrade() >= lower
        && stud_list[i]->getGrade() < upper)
            num_grade++;
    }

    ios_base::fmtflags old_flags = file_out.flags();
    int old_precision = file_out.precision();

    file_out.width(4);
    file_out << right;
    file_out << num_grade;
    file_out << endl;

    file_out.flags(old_flags);
    file_out.precision(old_precision);

}


/* Helper function for formatting class breakdowns. The desired subject is
 * passed in and all students belonging to that major are found and output to
 * the stream in an organized manner. */
void StudentList::showSubject(ofstream &file_out, const char *course_name,
                              Subject subject) const {
    file_out << course_name << " CLASS\n\n";
    file_out <<
             "Student                                   Final Final   Letter\n"
             "Name                                      Exam  Avg     Grade\n"
             "-----------------------------------------------------------------"
             "-----\n";

    for (int i = 0; i < num_studs; i++) {
        if (stud_list[i]->getSubject() == subject)
            file_out << *stud_list[i];
    }

    file_out << endl << endl;
}