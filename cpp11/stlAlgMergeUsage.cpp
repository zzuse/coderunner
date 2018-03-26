#include <iostream>
#include <algorithm>
#include <array>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 5;
	array<int , SIZE> a1 = {1,3,5,7,9};
	array<int , SIZE> a2 = {2,4,5,7,9};
	ostream_iterator<int> output(cout," ");
	
	cout << "array a1 contains: ";
	copy(a1.cbegin(),a1.cend(),output);
	cout << "\narray a2 contains: ";
	copy(a2.cbegin(),a2.cend(),output);
	
	array<int, SIZE> results;
	
	copy_backward(a1.cbegin(), a1.cend(), results.end());
	cout << "\n\nAfter copy_backward, results contains: ";
	copy(results.cbegin(), results.cend(), output);
	
	array<int, SIZE+SIZE> results2;
	
	merge(a1.cbegin(), a1.cend(), a2.cbegin(), a2.cend(), results2.begin());
	
	cout << "\n\nAfter merge of a1 and a2 results2 contains: ";
	copy(results2.cbegin(),results2.cend(),output);
	
	auto endLocation = unique(results2.begin(), results2.end());
	
	cout << "\n\nAfter unique results2 contains: ";
	copy(results2.begin(),endLocation,output);
	
	cout << "\n\narray a1 after reverse: ";
	reverse(a1.begin(), a1.end());
	copy(a1.cbegin(),a1.cend(),output);
	cout << endl;
}