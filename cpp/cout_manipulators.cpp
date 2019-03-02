#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
	cout << "Before using showpoint"<< endl
	<< "9.9900 prints as: "<<9.9900 << endl
	<< "9.9000 prints as: "<<9.9000 << endl
	<< "9.0000 prints as: " << 9.0000 << endl << endl;
	
	cout << showpoint
	<< "After using showpoint" << endl
	<< "9.9900 prints as: " << 9.9900 << endl
	<< "9.9000 prints as: " << 9.9000 << endl
	<< "9.0000 prints as: " << 9.0000 << endl << endl;
	
	int x=12345;
	cout << "Default is right justified:" << endl
	<< setw(10) << x << setw(10) << 123;
	cout << "\n\nUse std::left to left justify x:\n"
	<< left << setw(10) << x << setw(10) << 123;

	cout << "\n\nUse std::right to right justify x:\n"
	<<right<<setw(10)<<x<<endl<<endl;
	
	cout << internal << noshowpos << setw(10) << -123 << endl << endl;
	
	x = 10000;
	cout << x << " printed as int right and left justified\n"
	<< "and as hex with internal jusitfication.\n"
	<< "Using the default pad character (space):" << endl ;
	
	cout << showbase << setw(10) << x << endl;
	
	cout << left << setw(10) << x << endl;
	
	cout << internal << setw(10)  << hex << x << endl << endl;
	
	cout << "Using various padding characters:" << endl ;
	
	cout << right;
	cout.fill('*');
	cout << setw(10) << dec << x << endl;
	cout << left << setw(10) << setfill('%') << x << endl;
	cout << right << setw(10) << x << endl;

	cout << internal << setw(10) << setfill('^') << hex << x << endl << endl;
	
	x = 100;
	cout << "Printing integers preceded by their base:" << endl << showbase;
	
	cout << dec << x << endl;
	cout << oct << x << endl;
	cout << hex << x << endl << endl;
	
	{
		double x = 0.001234567;
		double y = 1.946e9;
		
		cout << "Displayed in default format:" << endl
		<< x << '\t' << y << endl;
		
		cout << "\nDisplayed in scientific format:" << endl 
		<< scientific << x << '\t' << y << endl;
		
		cout << "\nDisplayed in fixed format:" << endl 
		<< fixed << x << '\t' << y << endl << endl;
	}
	
	cout << "Printing uppercase letters in scientific" << endl 
	<< "notation exponents and hexadecimal values: " << endl;
	cout << scientific << uppercase << 4.345e10 << endl
	<< hex << showbase << 123456789 << endl << dec << endl;
	
	{
		bool booleanValue = true;
		cout << "booleanValue is " << booleanValue << endl;
		cout << "booleanValue (after using boolalpha ) is "
		<< boolalpha << booleanValue << endl << endl;
		
		cout << "switch booleanValue and use noboolalpha" << endl;
		booleanValue = false;
		cout << noboolalpha << endl;
		
		cout << "booleanValue is " << booleanValue << endl;
		
		cout << "booleanValue (after using boolalpha) is "
		<< boolalpha << booleanValue << endl << noboolalpha<< endl;
		
	}
	
	{
		int integerValue = 1000; 
		double doubleValue = 0.0947628;
		
		cout << "The value of the flags variable is: " << cout.flags()
		<< "\nPrint int and double in original format:\n"
		<< integerValue << '\t' << doubleValue << endl << endl;
		
		ios_base::fmtflags originalFormat = cout.flags();
		cout << showbase << oct << scientific;
		
		cout << "The value of the flags variable is:" << cout.flags()
		<< "\nPrint int and double in a new format:\n"
		<< integerValue << '\t' << doubleValue << endl << endl;
		
		cout.flags(originalFormat);
		cout << "The restored value of the flags variable is: "
		<< cout.flags() 
		<< "\nPrint values in original format again:\n"
		<< integerValue << '\t' << doubleValue << endl << endl;
	}
	
	{
		int integerValue;
		cout << "Before a bad input operation:"
		<< "\ncin.rdstate(): " << cin.rdstate()
		<< "\n    cin.eof(): " << cin.eof()
		<< "\n    cin.fail(): " << cin.fail()
		<< "\n    cin.bad(): " << cin.bad()
		<< "\n    cin.good(): " << cin.good()
		<< "\n\nExpects an integer, but enter a character: ";
		
		cin >> integerValue;
		cout << endl;
		
		cout << "After a bad input operation:"
		<< "\ncin.rdstate(): " << cin.rdstate()
		<< "\n    cin.eof(): " << cin.eof()
		<< "\n    cin.fail(): " << cin.fail()
		<< "\n    cin.bad(): " << cin.bad()
		<< "\n    cin.good(): " << cin.good() << endl << endl;
		
		cin.clear();
		cout << "After cin.clear()" << "\ncin.fail(): " << cin.fail()
		<< "\ncin.bad(): " << cin.bad()
		<< "\ncin.good(): " << cin.good() << endl;
	}
}