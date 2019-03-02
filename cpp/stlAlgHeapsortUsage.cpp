#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 10;
	array<int, SIZE> init = { 3,100,52,77,22,31,1,98,13,40 };
	array<int, SIZE> a(init);
	ostream_iterator<int> output(cout, " ");
	
	cout << "Array a before make_heap:\n";
	copy(a.cbegin(), a.cend(),output);
	
	make_heap(a.begin(), a.end());
	cout << "\nArray a after make_heap:\n";
	copy(a.cbegin(), a.cend(), output);
	
	sort_heap(a.begin(), a.end());
	cout << "\nArray a after sort_heap:\n";
	copy(a.cbegin(),a.cend(),output);
	
	cout << "\n\nArray init contains: ";
	copy(init.cbegin(), init.cend(), output);
	cout << endl;
	
	vector<int> v;
	
	for(size_t i = 0; i< SIZE; ++i)
	{
		v.push_back(init[i]);
		push_heap(v.begin(), v.end());
		cout << "\nv after push_heap(init[" << i << "]): ";
		copy(v.cbegin(), v.cend(), output);
	}
	
	cout << endl;
	
	for(size_t j = 0; j < v.size(); ++j )
	{
		cout << "\nv after " << v[0] << " popped from heap\n";
		pop_heap(v.begin(), v.end() - j);
		copy(v.cbegin(), v.cend(), output);
	}
	
	cout << endl;
}