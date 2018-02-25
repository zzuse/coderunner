#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <random>
#include <array>
#include "gradeBook.h"

using namespace std;

GradeBook::GradeBook(const std::string &name, const std::array<std::array<int, tests>, students> &gradesArray)
	: courseName (name), grades(gradesArray)
	{
	}
void GradeBook::setCourseName(string name){
		courseName = name;
	}
string GradeBook::getCourseName() const
{
	return courseName;
}
void GradeBook::displayMessage() const
{
	cout << "Welcome to Grade Book for " <<getCourseName() << "!"  <<endl;
}
void GradeBook::processGrades() const
{
	outputGrades();
	cout<<setprecision(2)<<fixed;
	cout<<"\nLoweast grade is "<<getMinimum()<< "\nHighest grade is " << getMaximum()<<endl;
	outputBarChart();
}
int GradeBook::getMinimum() const
{
	int lowGrade = 100;
	for (auto const &student:grades)
	{
		for (auto const &grade:student)
		{
			if (grade < lowGrade)
			{
				lowGrade = grade;
			}
		}
	}
	return lowGrade;
}
int GradeBook::getMaximum() const
{
	int highGrade = 0;
	for (auto const &student:grades)
	{
		for(auto const &grade:student)
		{
			if (grade > highGrade)
			{
				highGrade = grade;
			}
		}
	}
	return highGrade;
}
double GradeBook::getAverage(const std::array<int,tests> &setOfGrades) const
{
	int total = 0;
	for(int grade:setOfGrades)
		total+=grade;
	return static_cast<double> (total)/setOfGrades.size();
}
void GradeBook::outputBarChart() const
{
	cout<<"\nOutput distribution"<<endl;
	const size_t frequencySize = 11;
	array<unsigned int, frequencySize> frequency = {};
	for (auto const &student:grades)
		for (auto const &grade:student)
			++frequency[grade/10];
	for (size_t count = 0; count < frequencySize; ++count)
	{
		if( 0 == count)
			cout << "0-9: ";
		else if( 10 == count) {
			cout <<" 100:";
		}
		else 
			cout << count*10 << "-" << count*10+9 << ": ";
			
		for (unsigned int stars=0;stars< frequency[count];++stars)
		{
			cout << '*';
		}
		cout<<endl;
	}
}
void GradeBook::outputGrades() const
{
	cout << "\nThe grades are:\n\n";
	for( size_t test = 0; test < tests; ++test)
		cout << "Test " << test+1 << " ";
	cout << "Average" << endl;
	
	for (size_t student = 0;student < grades.size();++student)
	{
		cout << "Student "<< setw(2) << student +1 ;
		for (size_t test = 0;test < grades[student].size();++test)
			cout <<setw(8) << grades[student][test];
	
		double average = getAverage(grades[student]);
		cout << setw(9) << setprecision(2) << fixed << average << endl;
	}
}

template < typename T >
auto maximum(T x, T y, T z)  -> T
{
	T maximumValue = x;
	if (y > maximumValue)
		maximumValue = y;
	if (z > maximumValue)
		maximumValue = z;
	return maximumValue;
};

int main(int argc, char *argv[]) {
	
	//log of a double
	cout<< log(2.718282) << endl;
	cout<< boolalpha << "Logical AND (&&)"
	  << "false && false: " << (false&&false)<<endl;
	
	//random engine
	default_random_engine engine(static_cast<unsigned int> (time(0)));
	uniform_int_distribution<unsigned int>randomInt(1,6);
	
	for (unsigned int counter =1; counter <=20;++counter)
	{
		cout << setw(10) << randomInt(engine);
		if (counter % 5 == 0)
			cout << endl;
	}
	
	//array
	std::array<std::string, 7> colors = { "red", "orange", "yellow", "green", "blue", "indigo", "violet" };
	cout<<"Unsorted\n";
	for(string color:colors)
		cout<< color << " ";
	sort(colors.begin(),colors.end());
	cout<<"\nSorted\n";
	for(string color:colors)
		cout<< color << " ";
	bool found = binary_search(colors.begin(),colors.end(),"indigo");
	cout <<"\nIndigo " << (found?"was":"was not") << " in colors"<< endl;
	
	//GradeBook
	const array<array<int,GradeBook::tests >, GradeBook::students > grades = 
		{87,96,70,
		 68,87,90,
		94,100,90,
		100,81,82,
		83,65,85,
		78,87,65,
		85,75,83,
		91,94,100,
		76,72,84,
		87,93,73};
	GradeBook myGradeBook("CS101 Introduction to C++ programming",grades);
	myGradeBook.displayMessage();
	myGradeBook.processGrades();
	
}