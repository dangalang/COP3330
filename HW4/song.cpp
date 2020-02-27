/* Name: Forrest Lang
 * Date: 25 FEB 2020
 * Section: 0005
 * Assignment: Homework 4
 * Due: 6 MAR 2020
 */

#include <iostream>
#include "song.h"

using namespace std;


/* Format song output for streams.  Fixed width title, artist, genre and size.
 * Size is converted to megabytes and displayed to 1 decimal place. Output
 * ends in a newline. */
ostream& operator<<(ostream& os, const Song& s) {
    ios_base::fmtflags oldflags = cout.flags();
    int oldprecision = os.precision();

    os.setf(ios::left);
    os.width(36);
    os << s.GetTitle();
    os.width(21);
    os << s.GetArtist();

    os.width(10);
    switch (s.GetCategory()) {
        case POP:
            os << "Pop";
            break;
        case ROCK:
            os << "Rock";
            break;
        case ALTERNATIVE:
            os << "Alt";
            break;
        case COUNTRY:
            os << "Ctry";
            break;
        case HIPHOP:
            os << "HH";
            break;
        case PARODY:
            os << "Par";
            break;
        default:
            os << "N/A";
    }

    os.setf(ios::right);
    os.width(9);
    os.precision(1);
    os << s.GetSize() / 1000.0;

    os << endl;
    os.precision(oldprecision);
    os.flags(oldflags);

    return os;
}


/* Default constructor for songs.  Force size to 0 and title and artists to
 * null character for suppressed string display.  Genre is left unset. */
Song::Song() {
    title[0] = '\0';
    artist[0] = '\0';
    size = 0;
}


/* Set title, artist, genre and size values of the song.  Title and artist
 * strings are limited to size constraints and appended with null terminator
 * to prevent seg fault on output when input strings are longer than desired
 * length.  Size is checked for positivity and defaults to 0 if input is
 * negative. */
void Song::Set(const char* t, const char* a, Style st, int sz) {

    int i = 0;
    do {
        title[i] = t[i];
        i++;
    } while (i - 1 < 35 && t[i - 1] != '\0');
    title[35] = '\0';

    i = 0;
    do {
        artist[i] = a[i];
        i++;
    } while (i - 1 < 20 && a[i - 1] != '\0');
    artist[20] = '\0';

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
