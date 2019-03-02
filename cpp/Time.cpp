#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Time.h"

using namespace std;

Time::Time(int hour, int minute, int second)
{	
	setTime(hour,minute,second);
}

Time &Time::setTime(int h, int m, int s )
{
	setHour(h);
	setMinute(m);
	setSecond(s);
	return *this;
}

Time &Time::setHour(int h)
{
	if(h>=0 && h<24)
		hour=h;
	else
		throw invalid_argument("hour must be 0-23");
		
	return *this;
}

unsigned int &Time::badSetHour(int hh)
{
	if(hh>=0 && hh<24)
		hour = hh;
	else throw invalid_argument("hour must be 0-23");
	return hour;
}

Time &Time::setMinute(int m)
{
	if(m>=0 &&m<60)
		minute = m;
	else 
		throw invalid_argument("minute must be 0-59");
	
	return *this;
}

Time &Time::setSecond(int s)
{
	if (s>=0 && s<60)
		second = s;
	else
		throw invalid_argument("second must be 0-59");
	
	return *this;
}

unsigned int Time::getHour() const
{
	return hour;
}

unsigned Time::getMinute() const
{
	return minute;
}
unsigned Time::getSecond() const
{
	return second;
}

void Time::printUniversal() const
{
	cout << setfill('0') << setw(2) << getHour() << ":"
	<<setw(2)<< getMinute() <<":"<<setw(2)<<getSecond();
}

void Time::printStandard() const
{
	cout<<((getHour()==0||getHour()==12)?12:getHour()%12)<<":"
	<<setfill('0')<<setw(2)<<getMinute()<<":"<<setw(2)
	<<getSecond()<<(getHour()<12?" AM":" PM");
}

int main()
{
	Time t1;
	Time t2{2};
	Time t3{21,34};
	Time t4(12,25,42);
	
	cout<<"\nThe initial universal time is ";
	t1.printUniversal();
	cout<<"\nThe initial standard time is ";
	t1.printStandard();
	
	cout<<"\nThe initial universal time is ";
	t2.printUniversal();
	cout<<"\nThe initial standard time is ";
	t2.printStandard();

	cout<<"\nThe initial universal time is ";
	t3.printUniversal();
	cout<<"\nThe initial standard time is ";
	t3.printStandard();

	cout<<"\nThe initial universal time is ";
	t4.printUniversal();
	cout<<"\nThe initial standard time is ";
	t4.printStandard();
		
	try{
		Time t5(23,59,99);
	}
	catch (invalid_argument &e)
	{
		cout<<"\nException: "<<e.what()<<endl;
	}
	
	Time t;
	unsigned int &hourRef = t.badSetHour(20);
	cout<<"\nValid hour "<< hourRef;
	hourRef=30;
	cout<<"\nInvalid hour after modification: " << t.getHour();
	
	t.badSetHour(12) = 74;
	cout<<"\n\n*************************\n"
	<<"POOR PRACTICE!!!\n"
	<<t.getHour()
	<<"\n*************************"<<endl;
	cout<<endl;
	
	Time wakeUp(6,45,0);
	const Time noon(12,0,0);
	wakeUp.setHour(18);
	//noon.setHour(12);//compilation error
	cout<<wakeUp.getHour()<<endl;
	cout<<noon.getMinute()<<endl;
	noon.printUniversal();
	cout<<endl;
	noon.printStandard();
	
	cout<<"\n*************************"<<endl;
	cout<<"For cascading test"<<endl;
	Time tt;
	tt.setHour(18).setMinute(30).setSecond(22);
	cout<< "Universal time: ";
	tt.printUniversal();
	cout << "\nStandard time: ";
	tt.printStandard();
	
	cout<< "\n\nNew standard time: ";
	tt.setTime(20, 20, 20).printStandard();
	cout<<endl;

}