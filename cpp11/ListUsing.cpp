#include <iostream>
#include <array>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;
template < typename T >
void printList(const list<T> &listRef);

int main(int argc, char *argv[]) {
	const size_t SIZE = 4;
	array<int, SIZE> ints = { 2, 6, 4, 8 };
	list< int > values;
	list< int > otherValues;
	
	values.push_front(1);
	values.push_front(2);
	values.push_back(4);
	values.push_back(3);
	
	cout << "values contains: ";
	printList(values);
	
	values.sort();
	cout << "\nvalues after sorting contains: ";
	printList(values);
	
	otherValues.insert(otherValues.cbegin(), ints.cbegin(), ints.cend());
	cout << "\nAfter insert, otherValues contains: ";
	printList(otherValues);
	
	values.splice(values.cend(), otherValues);
	cout << "\nAfter splice, values contains: ";
	printList(values);
	
	values.sort();
	cout << "\nAfter sort, values contains: ";
	printList(values);
	
	otherValues.insert(otherValues.cbegin(),ints.cbegin(), ints.cend());
	otherValues.sort();
	cout << "\nAfter insert and sort, otherValues contains: ";
	printList(otherValues);
	
	values.merge(otherValues);
	cout << "\nAfter merge:\n   values contains: ";
	printList(values);
	cout << "\n     otherValues contains: ";
	printList(otherValues);
	
	values.pop_front();
	values.pop_back();
	cout << "\nAfter pop_front and pop_back:\n    values contains: ";
	printList(values);
	
	values.swap(otherValues);
	cout << "\nAfter swap:\n values contains: ";
	printList(values);
	cout << "\n.   otherValues contains: ";
	printList(otherValues);
	
	values.assign(otherValues.cbegin(), otherValues.cend());
	cout << "\nAfter assign, values contains: ";
	printList(values);
	
	values.merge(otherValues);
	cout << "\nAfter merge, values contains: ";
	printList(values);
	
	values.remove(4);
	cout << "\nAfter remove(4), values contains: ";
	printList(values);
	cout << endl;
	
}

template <typename T>
void printList(const list <T> &listRef)
{
	if( listRef.empty() )
		cout << "List is empty";
	else {
		ostream_iterator<T> output(cout," ");
		copy(listRef.cbegin(), listRef.cend(), output );
	}
}








