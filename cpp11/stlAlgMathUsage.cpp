#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <iterator>

using namespace std;
bool greater9(int);
void outputSquare(int);
int calculateCube(int);

int main(int argc, char *argv[]) {
	const size_t SIZE = 10;
	array<int, SIZE> a1 = {1,2,3,4,5,6,7,8,9,10};
	ostream_iterator<int> output(cout," ");
	
	cout << "a1 before random_shuffle: ";
	copy(a1.cbegin(),a1.cend(),output);
	
	random_shuffle(a1.begin(), a1.end());
	cout << "\na1 after random_shuffle: ";
	copy(a1.cbegin(),a1. cend(), output);
	
	array<int, SIZE> a2 = { 100,2,8,1,50,3,8,8,9,10};
	cout << "\n\na2 contains: ";
	copy(a2.cbegin(),a2.cend(),output);
	
	int result = count(a2.cbegin(),a2.cend(),8);
	cout << "\nNumber of elements matching 8: " << result;
	
	result = count_if(a2.cbegin(), a2.cend(), greater9);
	cout << "\nNumber of elements matching greater than 9: " << result;
	
	cout << "\n\nMinimum element in a2 is: "
	<< *(min_element(a2.cbegin(), a2.cend()));

	cout << "\nMaximum element in a2 is: "
	<< *(max_element(a2.cbegin(), a2.cend()));
	
	auto minAndMax = minmax_element(a2.cbegin(), a2.cend());
	cout << "\nThe minimum and maximum elements in a2 are "
	<< *minAndMax.first << " and " << *minAndMax.second << ", respectively";
	
	cout << "\n\nThe total of the elements in a1 is: "
	<< accumulate(a1.cbegin(), a1.cend(), 0);
	
	cout << "\n\nThe square of every integer in a1 is:\n";
	for_each(a1.cbegin(), a1.cend(), outputSquare);
	
	array<int, SIZE> cubes;
	transform(a1.cbegin(), a1.cend(), cubes.begin(), calculateCube);
	cout << "\n\nThe cube of every integer in a1 is:\n";
	copy(cubes.cbegin(),cubes.cend(),output);
	cout << endl;
}

bool greater9(int value)
{
	return value > 9;
}

void outputSquare(int value)
{
	cout << value * value << ' ';
}

int calculateCube(int value)
{
	return value * value * value;
}
