// Matthew Chen
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include "playlist.h"

using namespace std;

void ShowMenu();
Style WhatCategory(char c);
bool IsCategory(char c);


int main()
{
    Playlist p;
    char c;
    ShowMenu();
    cin>>c;
    c = toupper(c);
    while(c != 'X')
    {
        switch(c)
        {
            case 'A':
            {
                char t[36], a[21];
                char st;
                int sz = 0;
                cout<<"Insert title: ";
                cin.ignore();
                cin.getline(t,36);
                cout<<"Insert artist: ";
                cin.getline(a,36);
                cout<<"Insert category: (P) - POP, (R) - ROCK, (A) - Alternative, (C) - Country, (H) - Hiphop, (Y) - Parody: ";
                cin>>st;
                st = toupper(st);
                if(!IsCategory(st))
                {
                    while(!IsCategory(st))
                    {   
                        cout<<"Invalid category, please re-enter \n";
                        cin>>st;
                        st = toupper(st);
                    }
                }
                cout<<"Insert size: ";
                cin.ignore();
                cin>>sz;
                while(sz <= 0)
                {
                    cout<<"Must enter a positive size.  Please re-enter \n";
                    cin>>sz;
                }
                Song s;
                s.Set(t,a,WhatCategory(st),sz);
                p.Add(s);
                break;
            }
            case 'F':
            {
                char str[36];
                cout<<"Enter search string (title or artist): \n";
                cin.ignore();
                cin.getline(str,36);
                p.Search(str);
                break;
            }
            case 'D':
            {
                char t[36];
                cout<<"Enter title to delete: ";
                cin.ignore();
                cin.getline(t, 36);
                p.Del(t);
                break;
            }
            case 'S':
                p.Print();
                break;
            case 'C':
            {
                char c;
                cout<<"Enter Category - (P)op, (R)ock, (A)lternative, (C)ountry, (H)iphop, or Parod(Y): ";
                cin>>c;
                if(!IsCategory(toupper(c)))
                {
                    while(!IsCategory(toupper(c)))
                    {   
                        cout<<"Invalid category, please re-enter \n";
                        cin>>c;
                    }
                }
                p.PrintCategory(WhatCategory(toupper(c)));
                break;
            }
            case 'Z':
                cout<<"Total size of playlist: "<<p.TotalSize()<<" kilobytes \n";
                break;
            case 'O':
                {
                    char c;
                    cout<<"Sort by (T) - Title or (A) - Artist: ";
                    cin>>c;
                    c = toupper(c);
                    cout<<c<<"\n";
                    if(c != 'T' && c != 'A')
                    {
                        while(c != 'T' && c != 'A')
                        {   
                            cout<<"Invalid choice, please re-enter \n";
                            cin>>c;
                            c = toupper(c);
                            cout<<c<<"\n";
                        }
                    } 
                    p.Sort(c);
                    break;
                }
            case 'M':
                ShowMenu();
                break;
            case 'X':
                break;
            default:
                "Invalid menu option, try again \n";
                break;
        }
        cin>>c;
        c = toupper(c);
    }
    cout<<"Goodbye! \n";
}

void ShowMenu()
{
    cout<<" A:   Add a song to the playlist \n F:   Find a song on the playlist \n D:   Delete a song from the playlist \n S:   Show the entire playlist \n C:   Category summary  \n Z:   Show playlist size \n O:   Sort playlist \n M:   Show this Menu \n X:   eXit the program \n";
}

Style WhatCategory(char c) // helper function for converting user input to a category
{
    if(c == 'P')
        return POP;
    else if(c == 'R')
        return ROCK;
    else if(c == 'A')
        return ALTERNATIVE;
    else if(c == 'C')
        return COUNTRY;
    else if(c == 'H')
        return HIPHOP;
    else if(c == 'Y')
        return PARODY;
}

bool IsCategory(char c)
{
    if(c == 'P' || c == 'R' || c == 'A' || c == 'C' || c == 'H'|| c == 'Y')
        return true;
    return false;
}