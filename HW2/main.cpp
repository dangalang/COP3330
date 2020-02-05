/* Test code for date class
 * Forrest Lang
 * 4 Feb 2020
 */

#include <iostream>
#include "date.h"

using namespace std;

int main() {
    // TODO: can 0 be a valid year?
    // TODO: is 0 a leap year?

    Date d1;
    d1.Increment(65+365+366-1);

    cout << "d1: "; d1.Show();
    d1.SetFormat('J');
    cout << "d1: "; d1.Show();

    return 0;
}
