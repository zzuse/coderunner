#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

using namespace std;

int sumSquares(int total, int value)
{
	return total + value * value;
}

template< typename T >
class SumSquaresClass
{
	public:
		T operator()(const T &total, const T &value)
		{
			return total + value * value;
		}
};

int main(int argc, char *argv[]) {
	const size_t SIZE = 10;
	array<int, SIZE> integers = {1,2,3,4,5,6,7,8,9,10};
	ostream_iterator<int> output(cout, " ");
	
	cout << "array integers contains:\n";
	copy(integers.cbegin(), integers.cend(), output);
	
	int result = accumulate(integers.cbegin(), integers.cend(), 0, sumSquares);
	
	cout << "\n\nSum of squares of elements in integers using "
	<< "binary\nfunction sumSquares: " << result;
	
	result = accumulate(integers.cbegin(), integers.cend(), 0, SumSquaresClass<int>());
	
	cout << "\n\nSum of squares of elements in integers using "
	<< "binary\nfunction object of type "
	<< "SumSquaresClass<int>: " << result << endl;
	
	SumSquaresClass<int> sumSquareObject;
	result = accumulate(integers.cbegin(), integers.cend(), 0, sumSquareObject);
	cout << "\nSum of squares of elements in integers using "
	<< "binary\nfunction object: " << result << endl;
}