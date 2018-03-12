#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "BasePlusCommissionEmployee.h"

using namespace std;

BasePlusCommissionEmployee::BasePlusCommissionEmployee(
	const string& first, const string & last, const string &ssn, double sales, double rate, double salary
):CommissionEmployee(first,last,ssn,sales,rate)
{
	setBaseSalary(salary);
}

void BasePlusCommissionEmployee::setBaseSalary(double salary)
{
	if(salary>=0.0)
		baseSalary = salary;
	else
		throw invalid_argument("Salary must be >= 0.0");
}

double BasePlusCommissionEmployee::getBaseSalary() const
{
	return baseSalary;
}

double BasePlusCommissionEmployee::earnings() const
{
	return getBaseSalary() + (CommissionEmployee::earnings())	;
}

void BasePlusCommissionEmployee::print() const
{
	cout << "base-salaried ";
	CommissionEmployee::print();
	cout << "\nbase salary " << getBaseSalary();
}

	//int main(int argc, char *argv[]) {
	//	BasePlusCommissionEmployee
	//		employee("Bob","Lewis","333-33-3333",5000,.04,300);
	//		
	//	cout << fixed << setprecision(2);
	//	
	//	cout << "Employee information obtained by get functions: \n"
	//	<<"\n name is " << employee.getFirstName() << ' ' << employee.getLastName()
	//	<<"\n Social security number is " << employee.getSocialSecurityNumber()
	//	<<"\n Gross sales is " << employee.getGrossSales()
	//	<<"\n Commission rate is " << employee.getCommissionRate()
	//	<<"\n Base salary is " << employee.getBaseSalary() << endl;
	//	
	//	employee.setBaseSalary(1000);
	//	cout << "Updated!\n";
	//	employee.print();
	//	
	//	cout << "\n\nEmployee's earnings: $" << employee.earnings() << endl;
	//}