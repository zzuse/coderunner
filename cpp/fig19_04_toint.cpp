#include <iostream>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
	string s("100hello");
	size_t index;
	
	int convertedInt = stoi(s);
	int convertedInt1 = stoi(s, nullptr, 10);
	int convertedInt2 = stoi(s, &index, 2);
	
	string s1("123.45hello");
	double convertedDouble = stod(s1);
	
	cout << convertedInt << endl;
	cout << convertedInt1 << endl;
	cout << convertedInt2 << endl;
	cout << index << endl;
	cout << convertedDouble << endl;

}