#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
	deque<double> values;
	ostream_iterator< double > output(cout, " ");
	
	values.push_front(2.2);
	values.push_front(3.5);
	values.push_back(1.1);
	
	cout << "values contains: ";
	
	for(size_t i = 0; i < values.size(); ++i)
		cout << values[i] << ' ';
		
	values.pop_front();
	cout << "\nAfter pop_front, values contains: ";
	copy(values.cbegin(),values.cend(), output);
	values[1]=5.4;
	cout << "\nAfter values[1] = 5.4, values contains: ";
	copy(values.cbegin(),values.cend(),output);
	cout << endl;
}