/* Name: Forrest Lang
 * Date: 25 FEB 2020
 * Section: 0005
 * Assignment: Homework 4
 * Due: 6 MAR 2020
 */

#include <iostream>
#include <cstring>
#include "song.h"


using namespace std;

class Playlist {
    friend ostream& operator<<(ostream& os, const Playlist& p);
public:
    Playlist();
    Playlist(const Playlist& p);
    ~Playlist();

    Playlist& operator=(const Playlist& p);

    bool add(const char* t, const char* ar, Style st, int sz);
    bool add(const Song& s);
    bool remove(const char* title);
    void Sort(char sort_choice);

    Playlist searchSongs(const char* title) const;
    Playlist searchArtists(const char* artist) const;
    Playlist getGenre(Style st) const;
    int getSize() const;
    int getCount() const;

private:
    void resize();
    int findNextArtist(int index);
    int findNextTitle(int index);

    Song * song_list;
    int list_size;
    int current_song;
};