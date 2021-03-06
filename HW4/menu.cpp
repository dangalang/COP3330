/* Name: Forrest Lang
 * Date: 25 FEB 2020
 * Section: 0005
 * Assignment: Homework 4
 * Due: 6 MAR 2020
 */

#include "playlist.h"
#include "song.h"
#include <iostream>
#include <cstring>

using namespace std;

Style getCategory();

int main() {
    Playlist playlist, search_results;
    char menu_choice;
    char sort_choice;
    char song_title[36];
    char song_artist[21];
    Style song_style;
    int song_size;
    int oldprecision;
    ios_base::fmtflags oldflags;
    const char* MENU = "       *** Playlist Menu ***\n"
                       "       A:   Add a song to the playlist \n"
                       "       F:   Find a song on the playlist \n"
                       "       D:   Delete a song from the playlist\n"
                       "       S:   Show the entire playlist\n"
                       "       C:   Category summary \n"
                       "       Z:   Show playlist size\n"
                       "       O:   Sort playlist\n"
                       "       M:   Show this Menu \n"
                       "       X:   Exit the program\n";

    // Initialize main menu loop
    cout << "*** Welcome to playlist manager ***\n";
    cout << MENU;
    do {
        cout << "> ";
        cin >> menu_choice;
        cin.get();

        switch(tolower(menu_choice)) {
            // Add a song to the playlist
            case 'a':
                cout << "Enter title: ";
                cin.getline(song_title, 36);
                cout << "Enter artist: ";
                cin.getline(song_artist, 21);
                song_style = getCategory();

                do {
                    cout << "Enter size: ";
                    cin >> song_size;
                    if (song_size < 0)
                        cout << "Must enter a positive size, please re-enter"
                                "...\n";
                } while (song_size < 0);

                playlist.add(song_title, song_artist, song_style, song_size);
                break;

            // Search for a song in the playlist
            case 'f':
                cout << "Enter search string (title or artist): ";
                cin.getline(song_title, 36);
                search_results = playlist.searchSongs(song_title);
                if (search_results.getCount() == 0)
                    search_results = playlist.searchArtists(song_title);
                if (search_results.getCount() == 0)
                    cout << song_title << ": not found\n";
                else
                    cout << search_results;
                break;

            // Delete a song from the playlist
            case 'd':
                cout << "Enter title to delete: ";
                cin.getline(song_title, 36);
                if (playlist.remove(song_title))
                    cout << "Song removed!\n";
                else
                    cout << song_title << " not found in the playlist\n"
                         << "* No deletion performed. *\n";
                break;

            // Show the entire playlist
            case 's':
                if (playlist.getCount() == 0)
                    cout << "No songs currently in playlist.\n\n";
                else {
                    cout << "*Title*                             *Artist*    "
                            "         *Style*   *Size (MB)*\n";
                    cout << playlist;
                }
                cout << "Number of songs = " << playlist.getCount() << endl;
                oldprecision = cout.precision();
                oldflags = cout.flags();
                cout << fixed;
                cout.precision(1);
                cout << "Total playlist size = "
                     << static_cast<double>(playlist.getSize()) / 1000.0
                     << " MB\n";
                cout.precision(oldprecision);
                cout.flags(oldflags);
                break;

            // Only show songs belonging to a specific category
            case 'c':
                search_results = playlist.getGenre(getCategory());
                cout << search_results;
                cout << "Total songs in this category = "
                     << search_results.getCount() << endl;
                oldprecision = cout.precision();
                oldflags = cout.flags();
                cout << fixed;
                cout.precision(1);
                cout << "Total file size = "
                     << static_cast<double>(search_results.getSize()) / 1000.0
                     << " MB\n";
                cout.precision(oldprecision);
                cout.flags(oldflags);
                break;

            // Show the current size of the playlist
            case 'z':
                cout << "Total size of playlist = " << playlist.getSize() <<
                " kilobytes\n";
                break;

            // Sort the playlist by title or artist
            case 'o':
                do {
                    cout << "Sort by (T)itle or (A)rtist: ";
                    cin >> sort_choice;
                    if (!strchr("at", tolower(sort_choice)))
                        cout << "Invalid option, please re-enter...\n";
                } while (!strchr("at", tolower(sort_choice)));
                playlist.Sort(sort_choice);
                break;

            // Redisplay the menu
            case 'm':
                cout << MENU;
                break;

            // Exit
            case 'x': break;

            default:
                cout << "Invalid menu choice, try again...\n";
        }

    } while (tolower(menu_choice) != 'x');

    return 0;
}


/* Request a character entry from the user and return the appropriate Style
 * enumeration.  If input is invalid, loop until a valid character is
 * provided. */
Style getCategory() {
    char song_genre;
    do {
        cout << "Enter category - (P)op, (R)ock, (A)lternative, (C)ountry, "
                "(H)iphop, Parod(Y): ";
        cin >> song_genre;
        cin.get();
        if (!strchr("prachy", tolower(song_genre)))
            cout << "Invalid category entry, please re-enter...\n";
    } while (!strchr("prachy", tolower(song_genre)));
    
    switch (tolower(song_genre)) {
        case 'p': return POP;
        case 'r': return ROCK;
        case 'a': return ALTERNATIVE;
        case 'c': return COUNTRY;
        case 'h': return HIPHOP;
        case 'y': return PARODY;
        default:  return POP;
    }
}
