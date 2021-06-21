#include <iostream>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
	string string1("Testing iterators");
	string::const_iterator iterator1 = string1.begin();
	
	cout << "string1 = " << string1
	<< "\n(Using iterator iterator1) string1 is: ";
	
	while (iterator1 != string1.end()) {
		cout << *iterator1;
		++iterator1;
	}
	cout << endl;
	for (char c:string1)
		cout << c;
	cout << endl;
	string::const_reverse_iterator iterator2 = string1.rbegin();
	while(iterator2 != string1.rend()) {
		cout << *iterator2;
		++iterator2;
	}
	cout << endl;
}