#include <string>
#include <iostream>

using namespace std;

class CreateAndDestroy
{
	public:
		CreateAndDestroy(int ID, string messageString):objectId(ID), message(messageString) {
			cout <<"Object "<< objectId << "   constructor runs.  "
			<< message << endl;
		}
		~CreateAndDestroy(){
			cout << ( objectId == 1 || objectId == 6 ? "\n": "");
			
			cout << "Object " << objectId << "    destructor runs. "
			<< message << endl;
		}
	private:
		int objectId;
		string message;
};

void create (void);

CreateAndDestroy first(1, "(global before main)");

int main()
{
	cout << "\nMAIN FUNCTION: EXECUTION BEGINS" << endl;
	CreateAndDestroy second(2,"(local automaic in main )");
	static CreateAndDestroy third(3, "(local static in main )");
	
	create();
	
	cout<< "\nMAIN FUNCTION : EXECUTION RESUMES" << endl;
	CreateAndDestroy fourth(4, "(local automatic in main)");
	
	cout << "\nMAIN FUNTION: EXECUTION ENDS" << endl;
}

void create(void)
{
	cout << "\nCREATE FUNTION:EXECUTION BEGINS" << endl;
	CreateAndDestroy fifth(5, "(local automaci in create )");
	static CreateAndDestroy sixth(6, "(local static in create)");
	CreateAndDestroy seventh(7,"(local automatic in create)");
	cout<< "\n CREATE FUNCTION: EXECUTION ENDS" << endl;
}