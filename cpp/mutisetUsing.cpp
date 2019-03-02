#include <array>
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 10;
	array<int, SIZE> a = {7,22,9,1,18,30,100,22,85,13};
	multiset<int, less<int> > intMultiset;
	ostream_iterator<int> output(cout," ");
	
	cout << "There are currently " << intMultiset.count(15)
	<< " values of 15 in the multiset\n";
	
	intMultiset.insert(15);
	intMultiset.insert(15);
	cout << "After inserts, there are " << intMultiset.count(15)
	<< " values of 15 in the multiset\n\n";
	
	auto result = intMultiset.find(15);
	
	if( result != intMultiset.end() )
		cout << "Found value 15\n";
	
	result = intMultiset.find(20);
	
	if(result == intMultiset.end() )
		cout << "Did not find value 20\n";
	
	intMultiset.insert(a.cbegin(), a.cend());
	cout << "\nAfter insert, intMultiset contains:\n";
	copy( intMultiset.begin(), intMultiset.end(), output);
	
	cout << "\n\nLower bound 22: " 
		<< *(intMultiset.lower_bound(22) )
		<< "\n\nUpper bound 22: "
		<< *( intMultiset.upper_bound(22) );
	
	auto p = intMultiset.equal_range(22);
	
	cout << "\n\nequal_range of 22:" << "\n    Lower bound: "
	<< *(p.first) << "\n    Upper bound: " << *(p.second);
	cout << endl;	
}