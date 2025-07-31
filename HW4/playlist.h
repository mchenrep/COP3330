// Matthew Chen
#include <iostream>
#include "song.h"

using namespace std;

class Playlist
{
    public:
        Playlist(); // constructor 
        ~Playlist(); // destructor 

        void Print() const; // accessor to print the entire playlist
        int GetSize() const; // accessor for the size of the array
        void Search(const char* str) const; // accessor for searching and printing based off title/artist
        void PrintCategory(Style s) const; // accessor for printing out every song in a category and total songs and size
        int TotalSize() const; // accessor that returns total size of songs in playlist

        void Add(Song s); // mutator to add song to playlist
        void Del(const char* title); // mutator to delete song from playlist
        void Sort(char c); // mutator to sort the playlist by title or artist

    private:
        int size; // tracks size of dynamic array
        int max; // tracks used slots of the array
        Song * playlist; // dynamically allocated array of Songs (a playlist)
        void Grow(); // grows array
        int Find(const char* title) const; // finds first instance of parameter as title or artist
};