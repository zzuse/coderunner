#include <iostream>
#include <array>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
	const size_t SIZE = 4;
	array<int, SIZE> values = {1,2,3,4};
	
	for_each(values.cbegin(), values.cend(), [](int i){ cout << i*2 << endl;});
	
	int sum = 0;
	for_each(values.cbegin(), values.cend(), [&sum](int i) {sum += i;});
	cout << "sum is " << sum << endl;
}