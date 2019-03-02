#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE1 = 10, SIZE2 = 5, SIZE3 = 20;
	array<int, SIZE1> a1 = {1,2,3,4,5,6,7,8,9,10};
	array<int, SIZE2> a2 = {4,5,6,7,8};
	array<int, SIZE2> a3 = {4,5,6,11,15};
	ostream_iterator<int> output(cout," ");
	
	cout << "a1 contains: ";
	copy(a1.cbegin(),a1.cend(),output);
	cout << "\na2 contains: ";
	copy(a2.cbegin(),a2.cend(),output);
	cout << "\na3 contains: ";
	copy(a3.cbegin(),a3.cend(),output);
	
	if(includes(a1.cbegin(), a1.cend(), a2.cbegin(), a2.cend()))
	    cout << "\na1 includes a2 ";
	else
		cout << "\na1 does not include a2";
	if(includes(a1.cbegin(), a1.cend(), a3.cbegin(), a3.cend()))
		cout << "\na1 includes a3 ";
	else
		cout << "\na1 does not include a3";
		
	array<int, SIZE1> difference;
	
	auto result1 = set_difference(a1.cbegin(),a1.cend(),a2.cbegin(),a2.cend(),difference.begin());
	cout << "\n\nset_difference of a1 and a2 is: ";
	copy(difference.begin(), result1, output);
	
	array<int, SIZE1> intersection;
	auto result2 = set_intersection(a1.cbegin(),a1.cend(),a2.cbegin(),a2.cend(),intersection.begin());
	cout << "\n\nset_intersection of a1 and a2 is: ";
	copy(intersection.begin(), result2, output);
	
	array<int, SIZE1 + SIZE2> symmetric_difference;
	
	auto result3 = set_symmetric_difference(a1.cbegin(), a1.cend(), a3.cbegin(), a3.cend(), symmetric_difference.begin());
	cout << "\n\nset_symmetric_difference of a1 and a3 is: ";
	copy(symmetric_difference.begin(),result3, output);
	
	array<int, SIZE3> unionSet;
	auto result4 = set_union(a1.cbegin(), a1.cend(), a3.cbegin(), a3.cend(), unionSet.begin());
	cout << "\n\nset_union of a1 and a3 is: ";
	copy(unionSet.begin(), result4, output);
	cout << endl;
}