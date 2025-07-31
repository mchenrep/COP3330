#include <iostream>
#include <cstring>
#include <cctype>
#include "mystring.h"

using namespace std;

ostream& operator<< (ostream& os, const MyString& s)
{
    os<<s.getCString();
    return os;
}
istream& operator>> (istream& is, MyString& s) 
{
    int i = 0;
    char c;
    is.get(c);
    while(c != '\n')
    {
        s.grow(1);
        s[i] = c;
        i++;
        is.get(c);
    }
    s[s.size] = '\0';
    return is;
}

istream& getline (istream& is, MyString& s) 
{
    int i = 0;
    char c;
    is.get(c);
    while(c != '\n')
    {
        s.grow(1);
        s[i] = c;
        i++;
        is.get(c);
    }
    s[s.size] = '\0';
    return is;
}   

istream& getline (istream& is, MyString& s, char delim)
{
    int i = 0;
    char c;
    is.get(c);
    while(c != delim)
    {
        s.grow(1);
        s[i] = c;
        i++;
        is.get(c);
    }
    s[s.size] = '\0';
    return is;
}

MyString operator+ (const MyString& s, const MyString& s2) 
{
    MyString r = s;
    if(r.size < s2.getLength())
        r.grow(s2.getLength());
    strcat(r.str, s2.getCString());
    r.size = s.getLength() + s2.getLength();
    return r;
}

MyString operator- (const MyString& s, const MyString& s2) 
{
    MyString r = s;
    int i = 0;
    int sl = s.getLength();
    int s2l = s2.getLength();

    while(i < sl)
    {
        if(strstr(&s[i], s2.getCString()) == &s[i])
        {
            sl-=s2l;
            for(int j = i; j < sl; j++)
            {
                r[j] = r[j+s2l];
            }
        }
        else
            i++;
    }
    return r;
}

bool operator< (const MyString& s, const MyString& s2)
{
    bool r = true;
    if(strcmp(s.getCString(), s2.getCString()) >= 0)
    {  
        r = false;
    }
    return r;
}
bool operator> (const MyString& s, const MyString& s2)
{
    bool r = true;
    if(strcmp(s.getCString(), s2.getCString()) <= 0)
    {  
        r = false;
    }
    return r;
}

bool operator<=(const MyString& s, const MyString& s2)
{
    if(!(s > s2))
        return true;
    return false;
}
bool operator>=(const MyString& s, const MyString& s2)
{
    if(!(s < s2))
        return true;
    return false;
}
bool operator==(const MyString& s, const MyString& s2)
{
    bool r = true;
    if(strcmp(s.getCString(), s2.getCString()) != 0)
    {  
        r = false;
    }
    return r;
}
bool operator!=(const MyString& s, const MyString& s2)
{
    if(s == s2)
    {
        return false;
    }
    return true;
}

MyString::MyString()
{
    str = new char[2];
    strcpy(str, "");
    size++;
}

MyString::MyString(const char* c)
{
    str = new char[strlen(c)+1];
    strcpy(str,c);
    size = strlen(c);
}

MyString::MyString(int x)
{
    bool n = false;
    int l = 0;
    int c = x;

    if(x < 0) // checks if negative
    {
        n = true;
        x = -x;
    }

    while(c > 0) // gets length of x 
    {
        c/=10;
        l++;
    }
    size = l;
    

    if(n) // uses loop to turn the int into a cstring (but reversed)
    {
        str = new char[size + 1];
        for(int i = 0; i < size; i++)
        {
            char c = (x%10) + '0';
            str[i] = c;
            x/=10;
        }
        str[size] = '-';
    }
    else
    {
        str = new char[size];
        for(int i = 0; i < size; i++)
        {
            char c = (x%10) + '0';
            str[i] = c;
            x/=10;
        }
    }

    for(int i = 0; i < size/2; i++) // reverses the cstring
    {
        char t = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = t;
    }

}		

MyString::~MyString()
{
    delete [] str;
}

MyString::MyString(const MyString& s)
{
    size = strlen(s.getCString());
    str = new char[size + 1];
    for(int i = 0; i < size; i++)
        str[i] = s[i];
}		

MyString& MyString::operator=(const MyString& s)
{
    if(this != &s)
    {
        delete [] str;
        size = strlen(s.getCString());
        str = new char[size + 1];
        for(int i = 0; i < size; i++)
            str[i] = s[i];
    }
    return *this;
}

MyString& MyString::operator+=(const MyString& s) 
{
    strcat(str, s.getCString());
    return *this;
}
 
char& MyString::operator[] (unsigned int index)
{
    if(size < index)
    {
        grow((index-size));
    }
    return str[index];
}

const char& MyString::operator[] (unsigned int index) const
{
    if(size < index)
        return '\0';
    return str[index];
}


 MyString& MyString::insert(unsigned int index, const MyString& s) 
 {
    grow(s.getLength());
    int j = 0,c = 0;
    for(int i = index+s.getLength(); i <size; i++)
    {
        str[i] = str[index+(c++)];
    }
    for(int i = index; i < index+s.getLength(); i++)
    {
        str[i] = s[j++];
    }
    return *this;
 }

int MyString::indexOf(const MyString& s) const 
{
    int j = 0;
    bool found = true;
    for(int i = 0; i < size; i++)
    {
        if(str[i] == s[j])
        {
            for(int k = i; k < i+(s.getLength()-1); k++)
            {
                if(str[k] != s[j])
                    found = false;
                j++;
            }
            if(found)
                return i;
        }
    }
    return -1;
}

int MyString::getLength() const
{
    return strlen(str);
}

const char* MyString::getCString() const
{
    return str;
}

MyString MyString::substring(unsigned int index, unsigned int n) const
{
    MyString r;
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        r[j] = str[index+i];
        j++;
    }

    return r;
}

MyString MyString::substring(unsigned int index) const
{
    MyString r;
    int j = 0;
    for(int i = index; i < size; i++)
    {
        r[j] = str[i];
        j++;
    }

    return r;
}

void MyString::grow(int s)
{   
    char* nstr = new char[size+s+1];
    size += s;
    for(int i = 0; i < strlen(str); i++)
    {
        nstr[i] = str[i];
    }
    delete [] str;
    str = nstr;
}