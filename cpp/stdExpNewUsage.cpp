#include <iostream>
#include <new>
#include <cstdlib>

using namespace std;

void customNewHandler()
{
	cerr << "customNewHandler was called";
	abort();
}

int main(int argc, char *argv[]) {
	double *ptr[50];
	try {
		for(size_t i = 0;i<50;++i)
		{
			//ptr[i]=new (nothrow) double[500000000000];
			ptr[i] = new double[500000000000];
			cout << "ptr[" << i << "] points to 50,000,000 new doubles\n";
		}
	} catch (bad_alloc &memoryAllocationException) {
		cerr << "Exception occurred: "
		<< memoryAllocationException.what() << endl;
	}
	
	set_new_handler(customNewHandler);
	for(size_t i = 0; i< 50; ++i)
	{
		ptr[i] = new double[5000000000];
		cout << "ptra[" << i << "] points to 50,000,000 new doubles\n";
	}
}