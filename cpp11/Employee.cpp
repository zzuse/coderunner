#include <iostream>
#include "Employee.h"
#include "Date.h"

using namespace std;

unsigned int Employee::count=0;

unsigned int Employee::getCount()
{
	return count;	
}

Employee::Employee(const string &first, const string &last,const Date &dateOfBirth, const Date & dateOfHire):firstName(first),lastName(last),birthDate(dateOfBirth),hireDate(dateOfHire)
{
	++count;
	cout << "Employee object constructor: "
	<< firstName << ' '<< lastName << endl;
}

void Employee::print() const
{
	cout << lastName <<", " << firstName << "  Hired: ";
	hireDate.print();
	cout << "   Birthday: ";
	birthDate.print();
	cout <<endl;
}

Employee::~Employee()
{
	cout << "Employee object destructor: "
	<< lastName << ", " << firstName << endl;
	--count;
}

string Employee::getFirstName() const
{
	return firstName;
}

string Employee::getLastName() const
{
	return lastName;
}

int main(int argc, char *argv[]) {
	cout << "Number of employees before instantiation of any objects is "
	<< Employee::getCount() << endl;
	Date birth(7,24,1949);
	Date hire(3, 12, 1988);
	{
		Employee manager("Bob","Blue",birth,hire);
		cout<<endl;
		manager.print();
	}
	cout<<endl;
	{
		Employee e1("Susan","Baker", birth,hire);
		Employee e2("Robert", "Jones", birth,hire);
		cout << "Number of employees after objects are instantiated is "
		<< Employee::getCount();
		cout << "\n\nEmployee 1: "
		<< e1.getFirstName() << " " << e1.getLastName() << "\nEmployee 2: "
		<<e2.getFirstName() << " " << e2.getLastName() << "\n\n";
	}
	
	cout << "\nNumber of employees after objects are deleted is "
	<< Employee::getCount() << endl;
}