#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
int main(int argc, char *argv[]) {
	const char* const word = "again";
	cout << "Value of word is: " << word << endl
	<< "Value of static_cast is: "
	<< static_cast<const void*> (word) << endl;
	
	cout.put('A');
	cout.put('A').put('\n');
	cout.put(65);
	cout.put('\n');
	
	int number;
	cout << "Enter a decimal number: ";
	cin >> number;
	
	cout << number << " in hexadecimal is: " << hex << number << endl;
	cout << dec << number << " in octal is: " << oct << number << endl;
	
	cout << setbase(10) << number << " in decimal is: " << number << endl;
	
	double root2 = sqrt(2.0);
	int places;
	cout << "Square root of 2 with precisions 0-9." << endl
	<< "Precision set by ios_base member function "
	<< "precision:" << endl;
	cout << fixed;
	cout << cout.precision() << endl;
	cout << root2 << endl;

	
	for ( places = 0; places <= 9; ++places)
	{
		cout.precision(places);
		cout << root2 << endl;
	}
	
	cout << "\nPrecision set by stream manipulator "
	<< "setprecision:" << endl;
	
	for(places = 0; places <=9; ++ places)
		cout << setprecision(places) << root2 << endl;
		
	int widthValue = 4;
	char sentence [10];
	cout << "Enter a sentence:" << endl;
	cin.width(5);
	while (cin>>sentence) {
		cout.width(widthValue++);
		cout<< sentence << endl;
		cin.width(5);
	}
}