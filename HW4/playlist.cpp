/* Name: Forrest Lang
 * Date: 25 FEB 2020
 * Section: 0005
 * Assignment: Homework 4
 * Due: 6 MAR 2020
 */

#include <iostream>
#include <cstring>
#include "playlist.h"

using namespace std;


/* Output each song in the playlist to the stream. */
ostream& operator<<(ostream& os, const Playlist& p) {
    for (int i = 0; i < p.current_song; i++)
        os << p.song_list[i];

    return os;
}


/* Default constructor for Playlist object initializes an empty playlist to a
 * size of 5. */
Playlist::Playlist() {
    list_size = 5;
    current_song = 0;
    song_list = new Song[list_size];
}


/* Copy constructor for Playlist object. */
Playlist::Playlist(const Playlist& p) {
    list_size = p.list_size;
    current_song = p.current_song;
    song_list = new Song[list_size];
    for (int i = 0; i < current_song; i++)
        song_list[i].Set(p.song_list[i].GetTitle(),
                         p.song_list[i].GetArtist(),
                         p.song_list[i].GetCategory(),
                         p.song_list[i].GetSize());
}


/* Playlist destructor deletes dynamic memory allocation prior to
 * termination. */
Playlist::~Playlist() {
    delete [] song_list;
}


/* Assignment operator for playlist object creates new dynamic list and
 * updates size and song information. */
Playlist& Playlist::operator=(const Playlist& p) {
    if (this != &p) {
        delete [] song_list;

        list_size = p.list_size;
        current_song = p.current_song;
        song_list = new Song[list_size];
        for (int i = 0; i < current_song; i++)
            song_list[i] = p.song_list[i];
    }

    return *this;
}


/* Add a new song to the playlist. Check if the playlist needs to be resized.
 * If given size parameter is not positive, do nothing and return false,
 * otherwise update the next song with the given parameters. */
bool Playlist::add(const char *t, const char *ar, Style st, int sz) {
    if (current_song >= list_size) resize();
    if (sz > 0) {
        song_list[current_song++].Set(t, ar, st, sz);
        return true;
    } else
        return false;
}


/* Function overload for cleaner addition of song objects. */
bool Playlist::add(const Song& s) {
    return add(s.GetTitle(), s.GetArtist(), s.GetCategory(), s.GetSize());
}


/* Remove the first occurrence of the given song title. */
bool Playlist::remove(const char *title) {
    bool song_found = false;
    int location = 0;
    while (!song_found && location < current_song - 1) {
        if (strncmp(song_list[location].GetTitle(), title, 35) == 0)
            song_found = true;
        else
            location++;
    }
    if (song_found) {
        for (int i = location; i < current_song - 1; i++)
            song_list[i] = song_list[i + 1];
        current_song--;
        resize();
    }
    return song_found;
}


/* Sort the playlist lexicographically by either the artist names or song
 * titles.  Uses basic sort algorithm from ch 5 of textbook. */
void Playlist::Sort(char sort_choice) {
    int next_song;
    Song temp;
    switch (tolower(sort_choice)) {
        case 'a':
            for (int i = 0; i < current_song; i++) {
                next_song = findNextArtist(i);
                temp = song_list[i];
                song_list[i] = song_list[next_song];
                song_list[next_song] = temp;
            }
            break;
        case 't':
            for (int i = 0; i < current_song; i++) {
                next_song = findNextTitle(i);
                temp = song_list[i];
                song_list[i] = song_list[next_song];
                song_list[next_song] = temp;
            }
            break;
        default:
            break;
    }
}


/* Return a new playlist containing all songs that share the same title. */
Playlist Playlist::searchSongs(const char *title) const {
    Playlist results;
    for (int i = 0; i < current_song; i++) {
        if (strncmp(song_list[i].GetTitle(), title, 35) == 0)
            results.add(song_list[i]);
    }
    return results;
}


/* Return a new playlist containing all songs by the desired artist. */
Playlist Playlist::searchArtists(const char *artist) const {
    Playlist results;
    for (int i = 0; i < current_song; i++) {
        if (strncmp(song_list[i].GetArtist(), artist, 20) == 0)
            results.add(song_list[i]);
    }
    return results;
}


/* Return a new playlist containing all songs in the desired category. */
Playlist Playlist::getGenre(Style st) const {
    Playlist results;
    for (int i = 0; i < current_song; i++) {
        if (song_list[i].GetCategory() == st)
            results.add(song_list[i]);
    }
    return results;
}


/* Calculates the playlist size in kilobytes. */
int Playlist::getSize() const {
    int total_size = 0;
    for (int i = 0; i < current_song; i++)
        total_size += song_list[i].GetSize();
    return total_size;
}


/* Calculates the total number of songs in the playlist. */
int Playlist::getCount() const {
    return current_song;
}


void Playlist::resize() {
    if (current_song >= list_size) {
        list_size += 5;
        Song* temp = new Song[list_size];
        for (int i = 0; i < current_song; i++)
            temp[i] = song_list[i];
        delete [] song_list;
        song_list = temp;
    } else if (list_size - current_song > 5) {
        list_size -= 5;
        Song* temp = new Song[list_size];
        for (int i = 0; i < current_song; i++)
            temp[i] = song_list[i];
        delete [] song_list;
        song_list = temp;
    }
}


int Playlist::findNextArtist(int index) {
    int next_index = index;
    for (int i = index + 1; i < current_song; i++) {
        if (strncmp(song_list[next_index].GetArtist(),
                song_list[i].GetArtist(), 20) > 0)
            next_index = i;
    }
    return next_index;
}


int Playlist::findNextTitle(int index) {
    int next_index = index;
    for (int i = index + 1; i < current_song; i++) {
        if (strncmp(song_list[next_index].GetTitle(),
                song_list[i].GetTitle(), 35) > 0)
            next_index = i;
    }
    return next_index;
}
