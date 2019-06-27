#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

template< typename T>
void testStack(
	Stack<T> &theStack,
	const T &value,
	const T &increment,
	size_t size,
	const string &stackName
)
{
	cout << "\nPushing elements onto " << stackName << '\n';
	T pushValue = value;
	
	for (size_t i = 0; i < size; ++i)
	{
		theStack.push(pushValue);
		cout << pushValue << ' ';
		pushValue += increment;
	}
	
	cout << "\n\nPopping elements from " << stackName << '\n';
	
	while(!theStack.isEmpty())
	{
		cout << theStack.top() << ' ';
		theStack.pop();
	}
	cout << "\nStack is empty. Cannot pop." <<endl;
}

int main(int argc, char *argv[]) {
	Stack<double> doubleStack;
	const size_t doubleStackSize = 5;
	testStack(doubleStack, 1.1, 1.1, doubleStackSize, "doubleStack");
	
	Stack<int> intStack;
	const size_t intStackSize = 10;
	testStack(intStack, 1, 1, intStackSize, "intStack");
}