#include <iostream>
#include <algorithm>
#include <array>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 10;
	array<int, SIZE> a = {2,2,4,4,4,6,6,6,6,8};
	ostream_iterator<int> output(cout, " ");
	cout << "array a contains: \n";
	copy(a.cbegin(),a.cend(),output);
	
	auto lower = lower_bound(a.cbegin(), a.cend(), 6);
	cout << "\n\nLower bound of 6 is element "
	<< (lower - a.cbegin() ) << " of array a";
	
	auto upper = upper_bound(a.cbegin(), a.cend(), 6);
	cout << "\nUpper bound of 6 is elment "
	<< (upper - a.begin()) << " of array a";
	
	auto eq = equal_range(a.cbegin(), a.cend(), 6);
	cout << "\nUsing equal_range:\n Lower bound of 6 is element "
	<< (eq.first - a.cbegin() ) << " of array a";
	cout << "\n   Upper bound of 6 is element "
	<< (eq.second - a.cbegin() ) << " of array a";
	cout << "\n\nUse lower_bound to locate the first point\n"
	<< "at which 5 can be inserted in order";
	
	lower = lower_bound(a.cbegin(), a.cend(), 5);
	cout << "\n    Lower bound of 5 is element "
	<< (lower - a.cbegin()) << "of array a";
	cout << "\n\nUse upper_bound to locate the last point\n"
	<< "at which 7 can be inserted in order";
	
	upper = upper_bound(a.cbegin(), a.cend(), 7);
	cout << "\n   Upper bound of 7 is element "
	<< (upper - a.cbegin()) << " of array a";
	cout << "\n\nUse equal_range to locate the first and \n"
	<< "last point at which 5 can be inserted in order";
	
	eq = equal_range(a.cbegin(), a.cend(), 5);
	cout << "\n Lower bound of 5 is element "
	<< (eq.first - a.cbegin() ) << " of array a";
	cout << "\n  Upper bound of 5 is element "
	<< (eq.second - a.cbegin() ) << " of array a " << endl;
	
}