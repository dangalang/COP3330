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
    char* song_title;
    char* song_artist;
    Style song_style;
    int song_size;
    int oldprecision;

    cout << "*** Welcome to playlist manager ***\n";
    do {
        cout << "       *** Playlist Menu ***\n"
                "  A:   Add a song to the playlist \n"
                "  F:   Find a song on the playlist \n"
                "  D:   Delete a song from the playlist\n"
                "  S:   Show the entire playlist\n"
                "  C:   Category summary \n"
                "  Z:   Show playlist size\n"
                "  M:   Show this Menu \n"
                "  X:   eXit the program\n";
        cout << "> ";
        cin >> menu_choice;

        switch(tolower(menu_choice)) {
            case 'a':
                cout << "Enter title: ";
                cin >> song_title;
                cout << "Enter artist: ";
                cin >> song_artist;
                do {
                    cout << "Enter size: ";
                    cin >> song_size;
                    if (song_size < 0)
                        cout << "Must enter a positive size, please re-enter"
                                "...\n";
                } while (song_size < 0);

                song_style = getCategory();
                playlist.add(song_title, song_artist, song_style, song_size);
                break;

            case 'f':
                cout << "Enter search string (title or artist): ";
                cin >> song_title;
                search_results = playlist.searchSongs(song_title);
                if (search_results.getCount() == 0)
                    search_results = playlist.searchArtists(song_title);
                if (search_results.getCount() == 0)
                    cout << song_title << ": not found\n";
                else
                    cout << search_results;
                break;

            case 'd':
                cout << "Enter title to delete: ";
                cin >> song_title;
                if (playlist.remove(song_title))
                    cout << "Song removed!\n";
                else
                    cout << song_title << " not found in the playlist\n"
                         << "* No deletion performed. *\n";
                break;

            case 's':
                cout << playlist;
                cout << "Number of songs = " << playlist.getCount() << endl;
                oldprecision = cout.precision();
                cout.precision(1);
                cout << "Total playlist size = "
                     << playlist.getSize() / 1000.0 << " MB\n";
                cout.precision(oldprecision);
                break;

            case 'c':
                search_results = playlist.getGenre(getCategory());
                cout << "Total songs in this category = "
                     << search_results.getCount() << endl;
                oldprecision = cout.precision();
                cout.precision(1);
                cout << "Total file size = "
                     << search_results.getSize() / 1000.0 << " MB\n";
                cout.precision(oldprecision);
                break;

            case 'z':
                cout << "Total size of playlist = " << playlist.getSize() <<
                " kilobytes\n";
                break;

            case 'o':
                do {
                    cout << "Sort by (T)itle or (A)rtist: ";
                    cin >> sort_choice;
                    if (!strchr("at", tolower(sort_choice)))
                        cout << "Invalid option, please re-enter...\n";
                } while (!strchr("at", tolower(sort_choice)));
                playlist.Sort(sort_choice);
                break;
            case 'm': break;
            case 'x': break;
            default:
                cout << "Invalid menu choice, try again...\n";
        }

    } while (tolower(menu_choice) != 'x');

    return 0;
}


Style getCategory() {
    char song_genre;
    do {
        cout << "Enter category - (P)op, (R)ock, (A)lternative, (C)"
                "ountry, (H)iphop, Parod(Y): ";
        cin >> song_genre;
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