#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main(int argc, char *argv[]) {
	string input("Input test 123 4.7 A");
	istringstream inputString(input);
	string string1;
	string string2;
	int integer;
	double double1;
	char character;
	
	inputString >> string1 >> string2 >> integer >> double1 >> character;
	
	cout << "The following items were extracted\n"
	<< "from the istringstream object:" << "\nstring: " << string1
	<< "\nstring: " << string2 << "\n   int: " << integer 
	<< "\ndouble: " << double1 << "\n   char: " << character;
	
	long value;
	inputString >> value;
	
	if(inputString.good())
		cout  << "\n\nlong value is: " << endl;
	else {
		 cout << "\n\ninputString is empty" << value << endl;
	}
}