// Matthew Chen
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include "playlist.h"

using namespace std;

Playlist::Playlist()
{
    max = 5;
    size = 0;
    playlist = new Song[max];
}

Playlist::~Playlist()
{
    delete [] playlist;
}

void Playlist::Print() const
{
    cout<<"Title\t\tArtist\t\tStyle\t\tSize(MB) \n";
    for(int i = 0; i < size; i++)
    {
        cout<<playlist[i]<<"\n";
    }
    cout<<"Total songs: "<< size << "\n";
    cout<<fixed<<setprecision(2)<<"Total size: "<<static_cast<double>(TotalSize())/1000 << " MB\n";
}

int Playlist::GetSize() const
{
    return size;
}

void Playlist::Search(const char* str) const
{
    bool found = false;
    if(Find(str) != -1)
    {
        cout<<str<<" found! \n";
        for(int i = 0; i < size; i++)
        {
            if(strcmp(str, playlist[i].GetTitle()) == 0 || strcmp(str, playlist[i].GetArtist()) == 0)
            {
                cout<<playlist[i]<<"\n";
                found = true;
            }
        }
    }
    else
        cout<<str<<" not found \n";
}

void Playlist::Add(Song s)
{
    if(size == max)
        Grow();

    playlist[size++] = s;
    cout<<"Song added \n";
}

void Playlist::Del(const char* title)
{
    int p = Find(title);
    if(p == -1)
    {
        cout<<title<<" not found in playlist \n";
        cout<<"* No deletion performed * \n";
    }
    else if(p != -1)
    {
        for(int i = p + 1; i < size; i++)
            playlist[i - 1] = playlist[i];
        size--;
        cout<<" Song removed \n";
    }
}

void Playlist::Grow()
{
    cout<<"Growing array \n";
    max = size + 5;
    Song * newList = new Song[max];

    for (int i = 0; i < size; i++)	// deep copy
	    newList[i] = playlist[i];

    delete [] playlist;
    playlist = newList;
}

void Playlist::Sort(char c)
{
    if(c == 'T')
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = i+1; j < size; j++)
            {
                if(strcmp(playlist[i].GetTitle(), playlist[j].GetTitle()) > 0)
                {
                    Song temp = playlist[i];
                    playlist[i] = playlist[j];
                    playlist[j] = temp;
                }
            }
        }
        cout<<"Sorted \n";
    }
    else if(c == 'A')
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = i+1; j < size; j++)
            {
                if(strcmp(playlist[i].GetArtist(), playlist[j].GetArtist()) > 0)
                {
                    Song temp = playlist[i];
                    playlist[i] = playlist[j];
                    playlist[j] = temp;
                }
            }
        }  
        cout<<"Sorted \n";              
    }
}


int Playlist::Find(const char* title) const
{
    for(int i = 0; i < size; i++)
    {
        if(strcmp(title, playlist[i].GetTitle()) == 0 || strcmp(title, playlist[i].GetArtist()) == 0)
            return i;
    }
    return -1;
}

void Playlist::PrintCategory(Style s) const
{   
    int total = 0, totalsize = 0;
    for(int i = 0; i < size; i++)
    {
        if(s == playlist[i].GetCategory())
        {
            cout<<playlist[i]<<"\n";
            total++;
            totalsize += playlist[i].GetSize();
        }
    }
    cout<<"Total songs in this category: "<<total<<"\n";
    cout<<fixed<<setprecision(2)<<"Total file size: "<<static_cast<double>(totalsize)/1000<<" MB \n";
}   

int Playlist::TotalSize() const
{
    int total = 0;
    for(int i = 0; i < size; i++)
        total += playlist[i].GetSize();
    return total;
}