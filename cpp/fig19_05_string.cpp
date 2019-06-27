#include <iostream>
#include <string>

using namespace std;

void printStatistics(const string& );
int main(int argc, char *argv[]) {
	string string1;
	cout << boolalpha << endl;
	cout << "Statistics before input:\n" << boolalpha;
	printStatistics(string1);
	
	cout << "\n\nEnter a string: ";
	cin >> string1;
	cout << "The string entered was: " << string1;
	cout << "\nStatistics after input:\n";
	printStatistics(string1);
	cin >> string1;
	cout << "\n\nThe remaining string is: " << string1 << endl;
	printStatistics(string1);
	
	string1 += "1234567890abcdefghijklmnopqrstuvwxyz1234567890";
	cout << "\n\nstring1 is now: " << string1 << endl;
	printStatistics(string1);
	
	string1.resize(string1.size() + 10);
	cout << "\n\nStats after resizing by (length + 10):\n";
	printStatistics(string1);
	cout << endl; 
	
}

void printStatistics(const string &stringRef)
{
	cout << "capacity: " << stringRef.capacity() << "\nmax size: "
	<< stringRef.max_size() << "\nsize: " << stringRef.size()
	<< "\nlength: " << stringRef.size()
	<< "\nempty: " << stringRef.empty();
}