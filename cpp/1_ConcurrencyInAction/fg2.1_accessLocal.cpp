#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

void do_something(int i){
//	sleep(i);
	++i;
}

struct func
{
	int &i;
	func(int& i_):i(i_)
	{
		printf("%d",i);
	}
	void operator()()
	{
		printf("%d",i);
		for(unsigned j=0;j<1000000;++j)
		{
			printf("%d",j);
			do_something(i);
		}
	}
};

void oops()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();
}

int main(int argc, char *argv[]) {
	oops();
}