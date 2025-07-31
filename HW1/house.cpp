#include <iostream>
#include <iomanip>
#include <cmath>
#include "house.h"

using namespace std;

House::House(int s, char b, char f) // constructor for House
{
	// error checking if size is over or under the limit (37 and 3) and setting them to the limit if so
	if(s > 37) 
		size = 37;
	else if(s < 3)
		size = 3;
	else
		size = s;
	
	// utilizing the setBorder and Fill functions for error checking
	setBorder(b);
	setFill(f);
}

int House::GetSize() const
{
	return size;
}

int House::Perimeter() const
{
	return size*3 + (size+2)*2 + 2; // perimeter of the house would be the base (size*3) and the roof (size+2 * 2) and the overhang (+2) 
}

double House::Area() const
{
	double ra  = (sqrt(3) / 4) * (size+2) ; // finding roof area (equilateral triangle area with each side being size+2) and casting it as a double
	return ra+(size*size); // returning roof area plus base area (square area with each side being size)
}

void House::Grow()
{
	if(size+1 <  37) // error checking if growing will be out of bounds, if not increase size by 1
		size++;
}

void House::Shrink()
{
	if(size-1 > 3)	// error checking if shrinking will be out of bounds, if not decrease size by 1
		size--;
}

void House::setBorder(char c)
{
	// checking if the ASCII code of the char is in bounds and setting the border to it, if not then set the border to default char
	if(int(c) > 32 && int(c) < 127)
		border = c;
	else
		border = 'x';
}

void House::setFill(char c)
{
	// checking if the ASCII code of the char is in bounds and setting the fill to it, if not then set the fill to default char
	if(int(c) > 32 && int(c) < 127)
                fill = c;
        else
                fill = '*';
}

void House::Draw() const
{
    int h = (size*2)+1; // formula for the height of the house
    int w = (size+2);  // formula for the width of the house (counting the overhang)

    for(int r = 0; r < h; r++)
    {
        for(int p = h-r; p > size; p--)
        {
            cout<<" "; // loop for the spaces creating the staircase-like roof which decreases each iteration until it reaches the base ( <= size)
        }
        for(int c  = 0; c < w; c++)
        {
            if(r == 0) // first row which only has 1 character being the border
            {
                if(c == w/2)
                    cout<<border<<" ";
            }
            else if(r == 1) // 2nd row which only has 2 characters both being borders
            {
                if(c == w/2 +1 || c == w/2 -1)
                    cout<<border<<" ";
            }
            if(r == h-1) // last row which only has borders after a space
            {
                if(c == 0 || c == w-1)
                    cout<<"  ";
                else
                    cout<<border<<" ";
            }
            else if(r == h/2 + 1) // middle row which has 2 borders and no spaces in front
            {
                if(c == 0 || c == 1 || c == w - 1 || c == w - 2)
                    cout<<border<<" ";
                else
                    cout<<fill<<" ";
            }
            else if(r > h/2 + 1) // for the base, border will always be the 2nd or 2nd to last unit
            {
                if(c == 0 || c == w - 1)
                    cout<<"  ";
                else if(c == 1|| c == w-2)
                    cout<<border<<" ";
                else
                    cout<<fill<<" ";
            }
            else if(r < h/2 + 1 && r > 1) // for the roof, using the spaces for the loop above, borders are placed right after the spaces and at the end of the row
            {
                if(c == h-r-size || c == w-1)
                    cout<<border<<" ";
                else if(c > h-r-size && c < w - 1)
                    cout<<fill<<" ";
            }
        }
        cout<<"\n";
    }	
}

	void House::Summary() const
{
	// making sure the function only returns the area (and other numbers) to 2 decimal places and basing the output statement  off of the sample run
	cout<<fixed<<setprecision(2)<<"Here is a summary on h3:"<<"\n"<<"House width and height base to roof = "<<size<<" units."<<"\n"<<"Perimeter of house = "<<Perimeter()<<" units."<<"\n"<<"Area of house = "<<Area()<<" units.";
}
