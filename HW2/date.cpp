#include <iostream>
#include "date.h"

using namespace std;

Date::Date()
// default constructor for date
{
	Set(1,1,2000);
}

Date::Date(int m, int d, int y)
// default constructor for date
{
	Set(m,d,y);
}

void Date::Show() const
// if format is valid, then output the date in that format
{
	switch (format)
	{
		case 'D':
			cout<<month<<"/"<<day<<"/"<<year<<"\n";
			break;
		case 'T':
			cout<<month<<"/";
			if(day < 10)
				cout<<"0"<<day;
			else
				cout<<day<<"/";
			if(year % 100 < 10)
				cout<<"0"<<(year % 100)<<"\n";
			else
				cout<<(year%100)<<"\n";
			break;
		case 'L':
			switch(month)
			{
				case 1:
					cout<<"January ";
					break;
				case 2:
					cout<<"February ";
					break;
				case 3:
					cout<<"March ";
					break;
				case 4:
					cout<<"April ";
					break;
				case 5:
					cout<<"May ";
					break;
				case 6:
					cout<<"June ";
					break;
				case 7:
					cout<<"July ";
					break;
				case 8:
					cout<<"August ";
					break;
				case 9:
					cout<<"September ";
					break;
				case 10:
						cout<<"October ";
					break;
				case 11:
						cout<<"November ";
					break;
				case 12:
						cout<<"December ";
					break;
			}
			cout<<day<<", "<<year<<"\n";
			break;
		case 'J':
		{
			int sum = 0; // adds up the days of previous months for julian day so that the end output is the day in current month + all the days of the previous month
			if(year % 100 < 10)
				cout<<"0"<<(year % 100)<<"-";
			else
				cout<<(year%100)<<"-";
			switch(month)
			{
				case 1:
					break;
				case 2:
					sum += 31;
					break;
				case 3:
					if(IsLeapYear(year))
						sum+=29;
					else
						sum+=28;
					break;
				case 4:
					sum += 31;
					break;
				case 5:
					sum += 30;
					break;
				case 6:
					sum += 31;
					break;
				case 7:
					sum += 30;
					break;
				case 8:
					sum += 31;
					break;
				case 9:
					sum += 31;
					break;
				case 10:
					sum += 30;
					break;
				case 11:
					sum += 31;
					break;
				case 12:
					sum += 30;
					break;
			}
			cout<<day+sum<<"\n";
		}
		default:
			break;
	}
}

void Date::Input()
// cin statement with char filler for the slashes
{
	char d; 
	do
	{
		cin>>month>>d>>day>>d>>year;
		if(!Set(month, day, year))
		{
			cout<<"Invalid date womp womp. Try again:"<<"\n";
		}
	} while (!Set(month, day, year)); 
	
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}
int Date::GetYear() const
{
	return year;
}

bool Date::Set(int m, int d, int y)
// where the error checking is done for each year, month, and day in the month
{
	if(m > 0 && m < 13)
		month = m;
	if(y > 0)
		year = y;
	switch(month)
	{
		case 1:
				if(day <= 31)
					return true;
				break;
		case 2:
			if(IsLeapYear(year))
			{
				if(day <= 29)
					return true;
			}
			else
			{
				if(day <= 28)
					return true;
			}
			break;
		case 3:
			if(day <= 31)
				return true;
			break;
		case 4:
			if(day <= 30)
				return true;
			break;
		case 5:
			if(day <= 31)
				return true;
			break;
		case 6:
			if(day <= 30)
				return true;
			break;
		case 7:
			if(day <= 31)
				return true;
			break;
		case 8:
			if(day <= 31)
				return true;
			break;
		case 9:
			if(day <= 30)
				return true;
			break;
		case 10:
				if(day <= 30)
					return true;
				break;
		case 11:
				if(day <= 31)
				return true;
			break;
		case 12:
				if(day <= 31)
					return true;
				break;
		default:
				break;
	}
	return false;
}

bool Date::SetFormat(char f)
// error checking for right format
{
	if(f == 'D' || f == 'T' || f == 'L' || f == 'J')
	{
		format = f;
		return true;
	}
	else
		return false;
}

void Date::Increment(int numDays)
{	
	if(Set(month, day + numDays, year))
		Set(month, day + numDays, year); // if the incrementation is valid, set it to that
	else if(EndOfTheMonth(month))
	{
		Set(month + 1, numDays, year); // if it's the end of the month, increment month and days
	}	
	else
	{
		for(int i = numDays; i > 0; i++)
		{
			if(!Set(month, day + numDays, year))
				numDays--;
		}
		/* after the loop, all invalid increments (in current month) are subtracted from numDays and we can logically
			deduce that the remaining numDays is how many days past the next month the date is */
		Set(month + 1, numDays, year);
	}
}

int Date::Compare(const Date& d) const
// if calling date > parmeter return -1, 0 if same, 1 if parameter > calling date
// compare years, then months, then days
{
	if(year == d.year && month == d.month && day == d.day) // checking if the dates are the same
		return 0;
	if(year > d.year) // checking if calling year, month, and day are greater than parameter
		return -1;
	else if(month > d.month)
		return -1;
	else if(day > d.day)
		return -1;
	return 1; // if none is larger then parameter is larger (duh.)
}

bool Date::EndOfTheMonth(int m) const
// helper function to determine if it's the end of the month
{
	switch(month)
	{
		case 1:
			if(day == 31)
				return true;
			break;
		case 2:
			if(IsLeapYear(year))
			{
				if(day == 29)
					return true;
			}
			else
			{
				if(day == 28)
					return true;
			}
			break;
		case 3:
			if(day == 31)
				return true;
			break;
		case 4:
			if(day == 30)
				return true;
			break;
		case 5:
			if(day == 31)
				return true;
			break;
		case 6:
			if(day == 30)
				return true;
			break;
		case 7:
			if(day == 31)
				return true;
			break;
		case 8:
			if(day == 31)
				return true;
			break;
		case 9:
			if(day == 30)
				return true;
			break;
		case 10:
			if(day == 30)
				return true;
			break;
		case 11:
			if(day == 31)
				return true;
			break;
		case 12:
			if(day == 31)
				return true;
			break;
		default:
			break;
	}
	return false;
}

bool Date::IsLeapYear(int m) const
// helper function to detect leap years
{
	if(m % 4 == 0 && (m /100) != 0) // regular leap year with error checking for century years
		return true; 
	else if(m % 400 == 0) // century leap year
		return true; 
	return false;
}