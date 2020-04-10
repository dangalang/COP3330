/* Name: Forrest Lang
 * Date: 2 APR 2020
 * Section: 0005
 * Assignment: Homework 6
 * Due: 10 APR 2020
 */

#include <iostream>
#include "StudentList.h"

using namespace std;

int main() {
    StudentList stud_list;
    char choice;
    char filename[30];
    const char* menu = "                 *** Student List menu ***\n\n"
                       "        I       Import students from a file\n"
                       "        S       Show student list (brief)\n"
                       "        E       Export a grade report (to file)\n"
                       "        M       Show this Menu\n"
                       "        Q       Quit Program\n";

    cout << menu;

    // MAIN PROGRAM LOOP
    do {
        cout << "> ";
        cin >> choice;
        switch(tolower(choice)) {

            // Import students from a file
            case 'i':
                cout << "Enter filename: ";
                cin >> filename;

                while(!stud_list.ImportFile(filename)) {
                    cout << "Invalid file name, please try again: ";
                    cin >> filename;
                }
                break;

            // Show student list
            case 's':
                stud_list.ShowList();
                break;

            // Export a grade report
            case 'e':
                cout << "Enter filename: ";
                cin >> filename;

                while(!stud_list.CreateReportFile(filename)) {
                    cout << "Invalid file name, please try again: ";
                    cin >> filename;
                }
                break;

            // Show menu again
            case 'm':
                cout << menu;
                break;

            // Quit program
            case 'q':
                break;

            default:
                cout << "Incorrect input, please try again: ";
        }
    } while (tolower(choice) != 'q');

    return 0;
}