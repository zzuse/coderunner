#include <array>
#include <iostream>
#include <stdexcept>
#include "Date.h"

using namespace std;

const array< unsigned int, 13> Date::days = {
		0,31,28,31,30,31,30,31,31,30,31,30,31
	};

Date::Date(int mn,int dy, int yr)
{
	setDate(mn,dy,yr);
}

void Date::setDate(int mm, int dd, int yy){
	if(mm>=1 && mm<=12)
		month=mm;
	else {
		throw invalid_argument("month must be 1-12");
	}
	
	if( yy >= 1900 && yy <=2100)
		year=yy;
	else {
		throw invalid_argument("year must be 1900-2100");
	}
	
	if((month==2 && leapYear(year) && dd>=1 && dd <=29 )|| (dd >=1 && dd <=days[month]))
		day = dd;
	else {
		throw invalid_argument("Day is out of range");
	}
}

Date &Date::operator++(){
	helpIncrement();
	return *this;
}

Date Date::operator++(int)
{
	Date tmp = *this;
	helpIncrement();
	return tmp;
}

Date &Date::operator+=(unsigned int additionalDays)
{
	for(int i =0;i<additionalDays;++i)
		helpIncrement();
	
	return *this;
}

bool Date::leapYear(int testYear)
{
	if(testYear % 400 ==0 ||
	(testYear % 100 != 0 && testYear % 4 == 0 ) )
		return true;
	else 
		return false;
}

bool Date::endOfMonth(int testDay) const
{
	if((month == 2) && leapYear(year) )
		return testDay == 29;
	else {
		return testDay==days[month];
	}
}

void Date::helpIncrement() {
	if (!endOfMonth(day))
		++day;
	else {
		if (month < 12)
		{
			++month;
			day =1 ;
		}
		else {
			++year;
			month = 1;
			day =1;
		}
	}
}

ostream &operator<< (ostream &output, const Date &d)
{
	static string monthName[13] = {
		"", "Jan", "Feb", "Mar", "Apr", "May",
		"June","July", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	output << monthName [d.month] << ' ' << d.day <<  ", " << d.year;
	return output;
}

Date::~Date()
{
	cout << "Date objedct destructor for date ";
	cout << endl;
}

int main()
{
	Date d1(12,27,2010);
	Date d2;
	
	cout << "d1 is " << d1 << "\nd2 is " << d2;
	cout << "\nd1+7 is " << (d1+=7);
	
	d2.setDate(2, 28, 2008);
	cout << "\nd2 after setDate is " << d2;
	cout << "\n++d2 is " << ++d2 << " leap year allow 29th" ;
	
	Date d3(7,13,2010);
	cout << "\n\nd3 is " << d3 << endl;
	cout << "++d3 is " << ++d3 << endl;
	cout << "d3 is " << d3;
	
	cout << "\n\nTesting the postfix \nd3 is " << d3 << endl;
	cout << "d3++ is " << d3++ << endl;
	cout << "d3 is  " << d3 << endl;
}