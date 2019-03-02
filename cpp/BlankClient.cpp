#include <iostream>
#include <fstream>
#include "ClientData.h"

using namespace std;
int main(int argc, char *argv[]) {
	ofstream outCredit("credit.dat",ios::out | ios::binary);
	
	if(!outCredit)
	{
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
	
	ClientData blankClient;
	
	cout << sizeof(ClientData);
	for(int i=0;i<100;++i)
	{
		outCredit.write(reinterpret_cast<const char*> (&blankClient),sizeof(ClientData));
	}
}