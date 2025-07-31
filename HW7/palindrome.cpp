// Matthew Chen Section 6>
#include <iostream>
#include <cstring>
#include <cctype>
#include "stack.h"

using namespace std;

int main()
{
    char s[101]; // string
    char sClean[101];
    char bs[101]; 
    strcpy(s, "");
    strcpy(bs, "");
    strcpy(sClean, "");
    Stack <char> st;

    cout<<"Please enter a string: \n";
    cin.getline(s, 101);
    int i=0;
    int index=0;
    for (i=0; i<strlen(s); i++) // cleans out the string of punctaution and special characters
    {
        if(isalpha(s[i]))
        {
            sClean[index] = toupper(s[i]);
            index++;
        }
    }
    sClean[index] = '\0';

   for(int i = 0; i < strlen(sClean); i++) // pushes it to the clean string
   {
        st.push(sClean[i]);
   }

   while(!st.isStackEmpty()) // while stack isn't empty reverse it onto bs (backwards string)
   {
        char temp;
        st.pop(temp);
        char tempArray[2];
        tempArray[0] = temp; 
        tempArray[1] = '\0';
        strcat(bs, tempArray);
   }

   if (strcmp(bs, sClean) == 0) // compare backwards with forward string to see if it's a palindrome
        cout<<s<<" is a palindrome\n";
    else
        cout<<s<<" is NOT a palindrome\n";



}


