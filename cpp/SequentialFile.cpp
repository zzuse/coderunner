#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void outputLine(int, const string &, double);

int main(int argc, char *argv[]) {
	{
		ofstream outClientFile("clients.txt",ios::out);
		if(!outClientFile)
		{
			cerr << "File could not be opened" << endl;
			exit(EXIT_FAILURE);
		}
		
		cout <<"Enter the account, name ,and balance." << endl
		<< "Enter end-of-file to end input.\n? ";
		
		int account;
		string name;
		double balance;
		
		while (cin >> account >> name >> balance) {
			outClientFile << account << ' ' << name << ' '
			<< balance << endl;
			cout << "? "; 
		}
	}
	{
		ifstream inClientFile("clients.txt", ios::in);
		
		if(!inClientFile)
		{
			cerr << "File could not be opened" << endl;
			exit(EXIT_FAILURE);
		}
		
		int account;
		string name;
		double balance;
		
		cout << left << setw(10) << "Account" << setw(13)
		<< "Name" << "Balance" << endl << fixed << showpoint;
		
		while (inClientFile >> account >> name >> balance) {
			outputLine(account, name, balance);
		}
  	}
}

void outputLine(int account, const string &name, double balance)
{
	cout << left << setw(10) << account << setw (13) << name 
	<< setw(7) << setprecision(2) << right << balance << endl;
}