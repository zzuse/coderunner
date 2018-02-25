#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "CommissionEmployee.h"
using namespace std;

CommissionEmployee::CommissionEmployee(
	const string & first, const string & last, const string &ssn, double sales, double rate)
	: firstName(first), lastName(last), socialSecurityNumber(ssn)
{
		setGrossSales(sales);
		setCommissionRate(rate);
}
	
void CommissionEmployee::setFirstName(const string &first)
{
	firstName = first;
}

string CommissionEmployee::getFirstName() const
{
	return firstName;
}

void CommissionEmployee::setLastName( const std::string &last)
{
	lastName = last;
}

string CommissionEmployee::getLastName() const
{
	return lastName;
}

void CommissionEmployee::setSocialSecurityNumber(const std::string &ssn)
{
	socialSecurityNumber = ssn;
}

string CommissionEmployee::getSocialSecurityNumber() const
{
	return socialSecurityNumber;
}

void CommissionEmployee::setGrossSales(double sales)
{
	if(sales >= 0.0)
		grossSales = sales;
	else 
		throw invalid_argument("Gross sales must be >= 0.0");
}

double CommissionEmployee::getGrossSales() const
{
	return grossSales;
}

void CommissionEmployee::setCommissionRate( double rate )
{
	if(rate>0.0 && rate<1.0)
		commissionRate = rate;
	else
		throw invalid_argument("Commssion rate must be > 0.0 and < 1.0");
}

double CommissionEmployee::getCommissionRate()const
{
	return commissionRate;
}

double CommissionEmployee::earnings() const
{
	return getCommissionRate() * getGrossSales();
}

void CommissionEmployee::print() const
{
	cout << "commission employee: "<< getFirstName() << ' ' << getLastName()
	<< "\nsocail security number: " << getSocialSecurityNumber()
	<< "\ngross sales: " << getGrossSales()
	<< "\ncommisson rate: " << getCommissionRate();
}

	//int main()
	//{
	//	CommissionEmployee employee("Sue", "Jones", "222-22-2222", 10000, .06);
	//	
	//	cout << fixed << setprecision(2);
	//
	//	cout << "Employee information " << endl;
	//	cout << employee.getFirstName() << ' ' << employee.getLastName() << ' ' << employee.getSocialSecurityNumber()
	//	<< ' ' << employee.getGrossSales() << ' ' << employee.getCommissionRate() << endl;
	//	
	//	employee.setGrossSales(8000);
	//	employee.setCommissionRate(.1);
	//	
	//	cout << "\nUpdate employee information" << endl;
	//	employee.print();
	//	cout << "\nEmployee's earnings: " << employee.earnings() << endl;
	//}


