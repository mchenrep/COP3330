// Matthew Chen Section 6
#include <iostream>
#include <string>
#include "studentlist.h"

using namespace std;

void PrintMenu();

int main()
{
    char c;
    PrintMenu();
    cin>>c;
    StudentList slist;
    while(toupper(c) != 'Q')
    {
        switch(toupper(c))
        {
            case 'I':
            {
                char filename[30];
                cout<<"Enter filename: ";
                cin>>filename;
                slist.ImportFile(filename);
                break;
            }
            case 'S':
                slist.ShowList();
                break;
            case 'O':
                slist.sort();
                break;
            case 'E':
            {
                char filename[30];
                cout<<"Enter filename: ";
                cin>>filename;
                slist.CreateReportFile(filename);
                break;
            }
            case 'M':
                PrintMenu();
                break;
            case 'Q':
                cout<<"Goodbye !\n";
                break;
            default:
                cout<<"Invalid input\n";
                break;
        }
        cin>>c;
    }
}

void PrintMenu()
{
    cout<<"        *** Student List menu ***\nI       Import students from a file\nS       Show student list (brief)\nO       sOrt student list\nE       Export a grade report (to file)\nM       Show this Menu\nQ       Quit Program\n";
}