#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdexcept>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 6;
	array< int ,SIZE> values = { 1,2,3,4,5,6 };
	vector< int > integers(values.cbegin(),values.cend());
	ostream_iterator<int> output(cout, " ");
	
	cout << "Vector integers contains: ";
	copy(integers.cbegin(), integers.cend(), output);
	
	cout << "\nFirst element of integers: " << integers.front()
	<< "\nLast element of integers: " << integers.back();
	
	integers[0] = 7;
	integers.at(2) = 10;
	
	integers.insert(integers.cbegin()+1, 22);
	cout << "\n\nContents of vector integers after changes: ";
	copy(integers.cbegin(),integers.cend(),output);
	
	try {
		integers.at(100) = 777;
	}
	catch (out_of_range &outOfRange)
	{
		cout << "\n\nException: " << outOfRange.what();
	}
	
	cout << "\nCapacity:" << integers.capacity() << endl;
	integers.erase(integers.cbegin());
	cout << "\n\nVector integers after erasing first element: ";
	copy(integers.cbegin(),integers.cend(),output);
	cout << "\nCapacity:" << integers.capacity() << endl;
	
	integers.erase(integers.cbegin(),integers.cend() );
	cout << "\nAfter erasing all elements, vector integers "
	<< (integers.empty() ? "is" : "is not") << " empty";
	integers.shrink_to_fit();
	cout << "\nCapacity:" << integers.capacity() << endl;
	
	integers.insert(integers.cbegin(), values.cbegin(), values.cend());
	cout << "\n\nContents of vector integers before clear: ";
	copy(integers.cbegin(),integers.cend(),output);
	cout << "\nCapacity:" << integers.capacity() << endl;
	integers.clear();
	cout << "\nAfter clear, vector integers "
	<< (integers.empty()?"is":"is not") << " empty" << endl;
	integers.shrink_to_fit();
	cout << "\nCapacity:" << integers.capacity() << endl;
}