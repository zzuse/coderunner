#include <iostream>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
	string string1("The airplane landed on time.");
	cout << string1.substr(7, 5) << endl;
	
	string first("one");
	string second("two");
	
	cout << "Before swap:\n first: " << first << "\nsecond: " << second;
	first.swap(second);
	cout << "\n\nAfter swap:\n first: " << first
	<< "\nsecond: " << second << endl;
}