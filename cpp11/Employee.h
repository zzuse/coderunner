#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Date.h"

class Employee
{
	public:
		Employee(const std::string &, const std::string &, const Date&, const Date&);
		void print() const;
		~Employee();
		
		std::string getFirstName() const;
		std::string getLastName() const;
		static unsigned int getCount();
	private:
		std::string firstName;
		std::string lastName;
		const Date birthDate;
		const Date hireDate;
		static unsigned int count;
};

#endif