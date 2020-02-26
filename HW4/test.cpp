// Forest Lang
// song.cpp test file

#include <iostream>
#include "song.h"

using namespace std;

int main() {
    cout << "*Title*                             *Artist*             *Style*"
            "   *Size (MB)*\n";
    Song song;
    song.Set("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz", "The "
                                                                  "Beatles", ALTERNATIVE, 400);
    cout << song;
    cout << song;

    return 0;
}
