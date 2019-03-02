#include <iostream>
#include <memory>
using namespace std;

class Integer
{
	public:
		Integer(int i = 0):value(i){
			cout << "Constructor for Integer " << value << endl;
		}
		~Integer()
		{
			cout << "Destructor for Integer " << value << endl;
		}
		void setInteger(int i)
		{
			value = i;
		}
		int getInteger() const
		{
			return value;
		}
		
	private:
		int value;
};


int main(int argc, char *argv[]) {
	cout << "Creating a unique_ptr object that points to an Integer\n";
	unique_ptr<Integer> ptrToInteger(new Integer(7));
	cout << "\nUsing the unique_ptr to manipulate the Integer\n";
	ptrToInteger->setInteger(99);
	
	cout << "Integer after setInteger: " << (*ptrToInteger).getInteger()
	<< "\n\nTerminating program"<< endl;
}