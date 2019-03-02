#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
int main(int argc, char *argv[]) {
	string s1("happy");
	string s2(" birthday");
	string s3;
	cout << "s1 is " << s1 << endl;
	cout << "s2 is " << s2 << endl;
	cout << "compare\n" << (s2 == s1 ? "true" : "false\n")
	<< (s2>s1 ? "true" : "false\n");
	
	if(s3.empty())
	{
		s3 = s1;
		cout << "\ns3 is " << s3 << endl;
	}
	s1 += s2 + " to you";
	cout << "s1+s2 " << s1 << endl;
	cout << "substr " << s1.substr(0,14) << " --- " << s1.substr(15) << endl;
	string s4(s1);
	cout << "s4 " << s4 << endl;
	s4 = s4;
	cout << "s4 " << s4 << endl;
	s1[0]='H';
	s1[6]='B';
	cout << "s1 " << s1 << endl;
	try {
		s1.at(30) = 'd';
	}
	catch (out_of_range &ex)
	{
		cout << "An exception occurred: "<< ex.what() << endl;
	}
}