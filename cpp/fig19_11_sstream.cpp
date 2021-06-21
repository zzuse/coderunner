#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main(int argc, char *argv[]) {
	ostringstream outputString;
	
	string string1("Output of several data types ");
	string string2("to an ostringstream object:");
	string string3("\n        double: ");
	string string4("\n           int: ");
	string string5("\naddress of int: ");
	
	double double1 = 123.4567;
	int integer = 22;
	
	outputString << string1 << string2 << string3 << double1
	<<string4 << integer << string5 << &integer;
	
	cout << "OutputString contains:\n" << outputString.str();
	
	outputString << "\nmore characters added";
	cout << "\n\nafter additional stream insertions,\n"
	<< "outputString contains:\n" << outputString.str() << endl;
}