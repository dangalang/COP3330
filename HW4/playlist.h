/* Name: Forrest Lang
 * Date: 25 FEB 2020
 * Section: 0005
 * Assignment: Homework 4
 * Due: 6 MAR 2020
 */

#include "song.h"


using namespace std;

class Playlist {

public:
    Playlist();
    ~Playlist();

    void add(const Song& s);
    void remove(const char* title);
    void Sort(bool sort_by_title);

    void searchSongs(const char* title) const;
    void searchArtists(const char* artist) const;
    void showList() const;
    void showGenre() const;

private:
    void getSize() const;

    Song * song_list;
    int list_size;
    int current_song;
};