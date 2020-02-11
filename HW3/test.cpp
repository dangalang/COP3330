// Forrest Lang
// test file for distance class

#include <iostream>
#include "distance.h"
#include "catch.h"

using namespace std;

int main() {
    // Check all constructor possibilities
    Distance d0;
    Distance d1(7);
    Distance d2(11);
    Distance d3(36);
    Distance d4(1234567);
    Distance d5(-4);
    Distance d6(0, 0, 0, 8);
    Distance d7(0, 0, 1, 7);
    Distance d8(0, 141, 2, 11);
    Distance d9(18, 3, 0, 9);
    Distance d10(1, 2000, 0, 0);
    Distance d11(1, 1, 5, 0);
    Distance d12(1, 1, 1, 15);
    Distance d13(1, 1, 1, -1);
    Distance d14(1, 1, -1, 1);
    Distance d15(1, -1, 1, 1);
    Distance d16(-1, 1, 1, 1);

    Distance d17 = 1;
    Distance d18 = 45;
    Distance d19 = 4321;
    d19 = 1234567;

    // Check pre- and post-fix incrementation and decrementation
    d1++;
    ++d1;
    d1--;
    --d1;

    // Check again when rounding feet/inches
    d2++;
    d2--;
    ++d2;
    --d2;
    d3--;
    d3++;

    // Check ostream overload
    cout << d0 << endl;
    cout << d1 << endl;
    cout << d7 << endl;
    cout << d9 << endl;
    cout << d11 << endl;

    // Check istream overload
    //while (d1 != 0) {
//    for (int i = 0; i < 3; i++) {
//        cout << "Enter distance (MI,YD,FT,IN): ";
//        cin >> d1;
//        cout << "You entered: " << d1 << endl;
//    }

    // Check addition and subtraction
    d1 = Distance(1,0,0,0);
    d2 = Distance(0,0,0,1);
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d1 - d2 = " << d1 - d2 << endl;
    d1 = Distance(0,0,0,0);
    d2 = Distance(0,0,0,1);
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d1 - d2 = " << d1 - d2 << endl;
    d1 = Distance(0,0,1,0);
    d2 = Distance(0,0,2,0);
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d1 - d2 = " << d1 - d2 << endl;
    d1 = Distance(1,0,0,0);
    d2 = Distance(1,0,0,1);
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d1 - d2 = " << d1 - d2 << endl;
    d1 = Distance(0,1,6,9);
    d2 = Distance(2,5,2,7);
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d1 - d2 = " << d1 - d2 << endl;

    // Check multiplication
    cout << "d1: " << d1 << endl;
    cout << "d1 * 5 = " << d1 * 5 << endl;
    cout << "d1 * 76 = " << d1 * 76 << endl;
    cout << "d1 * 2.5 = " << d1 * 2.5 << endl;
    cout << "d1 * -3 = " << d1 * -3 << endl;

    // Check comparison and equality
    d1 = Distance(0,0,0,2);
    d2 = Distance(0,0,0,3);
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d1 < d2: " << (d1 < d2 ? "true" : "false") << endl;
    cout << "d1 > d2: " << (d1 > d2 ? "true" : "false") << endl;
    cout << "d1 <= d2: " << (d1 <= d2 ? "true" : "false") << endl;
    cout << "d1 <= d1: " << (d1 <= d1 ? "true" : "false") << endl;
    cout << "d1 >= d2: " << (d1 >= d2 ? "true" : "false") << endl;
    cout << "d2 >= d2: " << (d2 >= d2 ? "true" : "false") << endl;
    cout << "d1 == d2: " << (d1 == d2 ? "true" : "false") << endl;
    cout << "d1 == d1: " << (d1 == d1 ? "true" : "false") << endl;
    cout << "d1 != d2: " << (d1 != d2 ? "true" : "false") << endl;
    cout << "d2 != d2: " << (d2 != d2 ? "true" : "false") << endl;
    cout << "d1 < 5: " << (d1 < 5 ? "true" : "false") << endl;
    cout << "d1 < 1234567: " << (d1 < 1234567 ? "true" : "false") << endl;
    cout << "d1 == 2: " << (d1 == 2 ? "true" : "false") << endl;

    return 0;
}
