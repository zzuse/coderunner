#include <iostream>
#include <future>

int find_the_answer_to_ltuae()
{
	return 42;
}

void do_other_stuff()
{}


using namespace std;
int main(int argc, char *argv[]) {
	std::future<int> the_answer=std::async(find_the_answer_to_ltuae);
	do_other_stuff();
	std::cout << "The answer is " << the_answer.get() << std::endl;
}