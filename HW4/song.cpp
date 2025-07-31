// Matthew Chen
#include <iostream>
#include <iomanip>
#include <cstring>
#include "song.h"

using namespace std;

ostream& operator<<(ostream& os, const Song& s)
{
    os << s.title << "\t\t" << s.artist << "\t\t";
    if(s.GetCategory() == POP)
        os << "POP";
    if(s.GetCategory() == ROCK)
        os<< "ROCK";
    if(s.GetCategory() == ALTERNATIVE)
        os << "Alt";
    if(s.GetCategory() == COUNTRY)
        os << "Cntry";
    if(s.GetCategory() == HIPHOP) 
        os << "HH";
    if(s.GetCategory()== PARODY)
        os << "Par";
    os << fixed << setprecision(2) << "\t\t" << static_cast<double>(s.GetSize())/1000 << "\n";
    return os;
}

Song::Song()
{
    Set("","", POP, 0);
}

void Song::Set(const char* t, const char* a, Style st, int sz)
{
    strcpy(title,t);
    strcpy(artist,a);
    category = st;
    size = sz;
}

const char* Song::GetTitle() const
{
    return title;
}

const char* Song::GetArtist() const
{
    return artist;
}

int Song::GetSize() const
{
    return size;
}

Style Song::GetCategory() const
{
    return category;
}