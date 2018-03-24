#include <iostream>
#include <algorithm>
#include <array>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 10;
	array<int, SIZE> a1 = {1,2,3,4,5,6,7,8,9,10};
	array<int, SIZE> a2(a1);
	array<int, SIZE> a3 = {1,2,3,4,1000,6,7,8,9,10};
	ostream_iterator<int> output(cout," ");
	
	cout << "a1 contains: ";
	copy(a1.cbegin(),a1.cend(),output);
	cout << "\na2 contains: ";
	copy(a2.cbegin(),a2.cend(),output);
	cout << "\na3 contains: ";
	copy(a3.cbegin(),a3.cend(),output);
	bool result = equal(a1.cbegin(),a1.cend(),a2.cbegin());
	cout << "\na1 " << (result ? "is" : "is not") << " equal to a2.\n";
	
	result = equal(a1.cbegin(),a1.cend(),a3.cbegin());
	cout << "a1 " << (result ? "is" : "is not") << " equal to a3.\n";
	
	auto location = mismatch(a1.cbegin(),a1.cend(),a3.cbegin());
	cout << "\nThere is a mismatch between a1 and a3 at location "
	<< (location.first - a1.begin()) << "\nwhere a1 contains " << *location.first << " and a3 contains " << *location.second << "\n\n";
	
	char c1[SIZE] = "HELLO";
	char c2[SIZE] = "BYE BYE";
	
	result = lexicographical_compare(begin(c1), end(c1), begin(c2), end(c2) );
	cout << c1 << (result ? " is less than ": " is greater than or equal to ") << c2 << endl;
}