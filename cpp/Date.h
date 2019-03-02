#ifndef DATE_H
#define DATE_H

#include <array>
#include <iostream>

class Date
{
	friend std::ostream &operator<<(std::ostream &, const Date &);
	public:
		static const unsigned int monthsPerYear=12;
		explicit Date(int =1,int =1, int = 1900);
		void setDate(int, int, int);
		Date &operator++();
		Date operator++(int);
		Date &operator+=(unsigned int);
		void print() const;
	    static bool leapYear(int testYear);
		bool endOfMonth(int testDay) const;

		~Date();
	private:
		unsigned int month;
		unsigned int day;
		unsigned int year;
		unsigned int checkDay(int) const;
		static const std::array<unsigned int, 13> days;
		void helpIncrement();
};
#endif