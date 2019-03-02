#include <iostream>
#include <stdexcept>
using namespace std;

class DivideByZeroException :public std::runtime_error
{
	public:
		DivideByZeroException():std::runtime_error("attempted to divide by zero") {}
};

double quotient(int numerator, int denominator)
{
	if(denominator == 0)
		throw DivideByZeroException();
	return static_cast<double> (numerator) / denominator;
}

int main(int argc, char *argv[]) {
	int number1;
	int number2;
	cout << "Enter tow integers (end-of-file to end): "
	while (cin >> number1 >> number2)
	{
		try {
			double result = quotient(number1, number2)
			cout << "The quotient is: " << result << endl;
		}
		catch (DivideByZeroException &diveideByZeroException)
		{
			cout << "Exception occurred: "
			<< diveideByZeroException.what() << endl;
		}
		cout << "\nEnter two integers "
	}
	cout << endl;
}