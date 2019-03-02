#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

using namespace std;

void outputVector(const vector<int> &);
void inputVector(vector<int> &);

int main(int argc, char *argv[]) {
	vector<int> integers1(7);
	vector<int> integers2(10);
	
	cout<<"Size of vector 1 is "<< integers1.size() << "\nafter init:" << endl;
	outputVector(integers1);
	
	cout<<"Size of vector 2 is "<< integers2.size() << "\nafter init:" << endl;
	outputVector(integers2);
	
	cout<<"Enter 17 integers:" << endl;
	inputVector(integers1);
	inputVector(integers2);
	cout<<"After Input:\nintegers1:"<<endl;
	outputVector(integers1);
	cout<<"\nintegers2:"<<endl;
	outputVector(integers2);
	
	cout<<"\nEvaluating:"<<endl;
	if(integers1!=integers2)
		cout<<"integers1 and integers2 not equal" <<endl;
	
	vector<int> integers3(integers1);
	cout<<"Integer3 size "<< integers3.size()<<endl;
	outputVector(integers3);
	if(integers1==integers3)
		cout<<"integers1 and integers3 equal" <<endl;

	cout<<"Assign inte2 to inte1"<<endl;
	integers1 = integers2;
	cout<<"integer1 pos:"<<&integers1<<endl;
	outputVector(integers1);
	
	cout<<"integer2 pos:"<<&integers2<<endl;
	outputVector(integers2);
	
	cout<<"\nevaluating inter1==inter2"<<endl;
	if(integers1 == integers2)
		cout<<"integers1 and integers2 are equal" <<endl;
	
	cout<<"\nintegers[5] is "<<integers1[5];
	
	integers1[5] = 1000;
	cout<<"Integer1:"<<endl;
	outputVector(integers1);
	
	try
	{
		cout<<"\nattampt to display integers1.at(15)"<< endl;
		cout<<integers1.at(15)<<endl;
	}
	catch (out_of_range &ex)
	{
		cerr<<"An exception occurred: "<< ex.what()<<endl;
	}
	
	cout<<"inter3 size:"<<integers3.size()<<endl;
	integers3.push_back(1000);
	cout<<"new inter3 size is:"<<integers3.size()<<endl;
	outputVector(integers3);

}

void outputVector(const vector<int > & array) 
{
	for(int item:array)
		cout<<item<<" ";
	cout<<endl;
}

void inputVector(vector<int> &array)
{
	for(int &item:array)
		cin>>item;
}