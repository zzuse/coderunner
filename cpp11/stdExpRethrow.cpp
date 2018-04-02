#include <iostream>
#include <exception>

using namespace std;

void throwException()
{
	try
	{
		cout << " Function throwException throws an exception\n";
		throw exception();
	}
	catch (exception&)
	{
		cout << " Exception handled in function throwException"
		<< "\n Function throwException rethrows exception";
		throw;
	}
	cout << "This also should not print\n";
}
int main(int argc, char *argv[]) {
	try {
		cout << "\nmain invokes function throwException\n";
		throwException();
		cout << "This should not print\n";
	} catch (exception&) {
		cout << "\n\nException handled in main\n";
	}
	
	cout << "Program control continues after catch in main\n";
}