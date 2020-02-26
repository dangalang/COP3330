/* Name: Forrest Lang
 * Date: 25 FEB 2020
 * Section: 0005
 * Assignment: Homework 4
 * Due: 6 MAR 2020
 */

#include "song.h"

using namespace std;

ostream& operator<<(ostream& os, const Song& s) {
    os << setw(35) << s.GetTitle();
    os << setw(20) << s.GetArtist();

    switch (s.GetCategory()) {
        case POP:
                os << setw(8) << "Pop";
                break;
        case ROCK:
            os << setw(8) << "Rock";
            break;
        case ALTERNATIVE:
            os << setw(8) << "Alt";
            break;
        case COUNTRY:
            os << setw(8) << "Ctry";
            break;
        case HIPHOP:
            os << setw(8) << "HH";
            break;
        case PARODY:
            os << setw(8) << "Par";
            break;
        default:
            os << setw(8) << "N/A";
    }

    os << setw(5) << s.GetSize();
    os << endl;

    return os;
}


Song::Song() {
    title[0] = '\0';
    artist[0] = '\0';
    size = 0;
}


void Song::Set(const char* t, const char* a, Style st, int sz) {
    strncpy(title, t, 35);
    strncpy(artist, a, 20);
    category = st;
    size = (sz > 0 ? sz : 0);
}


const char* Song::GetTitle() const {
    return title;
}


const char* Song::GetArtist() const {
    return artist;
}


int Song::GetSize() const {
    return size;
}


Style Song::GetCategory() const {
    return category;
}
