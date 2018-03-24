#include <iostream>
#include <array>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 5;
	array<double, SIZE> a = {2.1, 4.2, 9.5, 2.1, 3.7};
	set<double, less<double> > doubleSet(a.begin(), a.end());
	ostream_iterator<double> output(cout, " ");
	
	cout << "doubleSet contains: ";
	copy(doubleSet.begin(), doubleSet.end(), output);
	
	auto p = doubleSet.insert(13.8);
	cout << "\n\n " << *(p.first)
	<< (p.second ? " was" : " was not" ) << " inserted";
	cout << "\ndoubleSet contains: ";
	copy(doubleSet.begin(), doubleSet.end(), output);
	
	p = doubleSet.insert(9.5);
	cout << "\n\n " << *(p.first)
	<< (p.second ? " was " : " was not") << " inserted" ;
	cout << "\ndoubleSet contains: ";
	copy(doubleSet.begin(), doubleSet.end(), output);
	cout << endl;
}