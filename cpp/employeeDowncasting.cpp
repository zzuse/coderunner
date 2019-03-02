#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "CommissionEmployee.h"
#include "BasePlusCommissionEmployee.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << fixed << setprecision(2);
	vector <Employee *>	employees(3);
	
	employees[0]=new SalariedEmployee("John","Smith","111-11-1111",800);
	employees[1]=new CommissionEmployee("Sue","Jones","333-33-3333",10000,.06);
	employees[2]=new BasePlusCommissionEmployee("Bob","Lewis","444-44-4444",5000,.04,300);
	for(Employee *employeePtr:employees)
	{
		employeePtr->print();
		cout<<endl;
		BasePlusCommissionEmployee *derivedPtr = dynamic_cast<BasePlusCommissionEmployee*> (employeePtr);
		if(derivedPtr!=nullptr)
		{
			double oldBaseSalary = derivedPtr->getBaseSalary();
			cout << "old base salary: $" << oldBaseSalary << endl;
			derivedPtr -> setBaseSalary(1.10*oldBaseSalary);
			cout << "new base salary with 10% increase is: $"
			<<derivedPtr->getBaseSalary()<<endl;
		}
		cout << "earned $" << employeePtr->earnings() << "\n\n";
	}
	
	for (const Employee *employeePtr:employees)
	{
		cout << "deleting object of "
		<<typeid(*employeePtr).name()<<endl;
		delete employeePtr;
	}
}