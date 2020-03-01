// Forest Lang
// song.cpp test file

#include <iostream>
#include "song.h"
#include "playlist.h"

using namespace std;

int main() {
    Playlist p1, p2;
    p1.add("Hello 1", "World 1", ROCK, 100);
    p2.add("Hello 2", "World 2", ALTERNATIVE, 200);
    cout << "Playlist 1:\n" << p1;
    cout << "Playlist 2:\n" << p2;
    cout << "Copy playlist 2 into playlist 1\n";
    p1 = p2;
    cout << "Modify p2\n";
    p1.remove("Hello 2");
    cout << "Playlist 1:\n" << p1;
    cout << "Playlist 2:\n" << p2;

//    cout << "*Title*                             *Artist*             *Style*"
//            "   *Size (MB)*\n";
//    Song song;
//    song.Set("", "", ALTERNATIVE, 400);
//    cout << song;
//    cout << song;

    return 0;
}
