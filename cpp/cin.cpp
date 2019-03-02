#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
	std::cout << "Please, enter a number or a word: ";
	std::cout.flush();    // ensure output is written

	std::cin >> std::ws;  // eat up any leading white spaces
    int c = std::cin.peek();  // peek character

	if ( c == EOF ) return 1;
	if ( std::isdigit(c) )
	{
		int n;
		std::cin >> n;
		std::cout << "You entered the number: " << n << '\n';
	}
	else
	{
		std::string str;
		std::cin >> str;
		std::cout  << "You entered the word: " << str << '\n';
	}
	
	const int SIZE=10;
	char buffer1[SIZE];
	char buffer2[SIZE];
	char buffer3[SIZE];
	
	cout << "Enter a sentence:" << endl;
	cin.read(buffer1,5);
	
	cout.write(buffer1, cin.gcount());
	cout << endl;
	
	cout <<"Enter a sentence: "<<endl;
	cin >> buffer1;
		
	cout << "\nThe string read with cin was: " << endl
	<< buffer1 << endl << endl;
		
	cin.get(buffer2,SIZE);
	cout <<"The string read with cin.get was: " << endl << buffer2 << endl;
	
	cin.getline(buffer3, SIZE);
	cout << "\nThe sentence entered is:" << endl << buffer3 << endl;
	
	std::cout << "Please, enter a number or a word: ";
	
    c = std::cin.get();

	if ( (c >= '0') && (c <= '9') )
	{
		int n;
		std::cin.putback (c);
		std::cin >> n;
		std::cout << "You entered a number: " << n << '\n';
	}
	else
	{
		std::string str;
		std::cin.putback (c);
		getline (std::cin,str);
		std::cout << "You entered a word: " << str << '\n';
	}

	return 0;
}