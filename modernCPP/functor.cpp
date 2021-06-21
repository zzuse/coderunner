#include <iostream>
#include <functional>

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <array>
#include <numeric>
#include <map>

using namespace std;

struct adder {
	adder(int n): n_(n) {}
	int operator()(int x) const
	{
		return x + n_;
	}
	private:
		int n_;
};

adder add_2(2);

auto add_22 = adder(2);


auto add_222 = [](int x) {
	return x + 2;
};


auto adder = [](int n) {
	return [n](int x) {
		return x + n;
	};
};

template <typename T>
auto test1(T fn)
{
	return fn(2);
}

template <typename T>
auto test2(T& fn)
{
	return fn(2);
}

template <typename T>
auto test3(T* fn)
{
	return (*fn)(2);
}


int get_count()
{
	static int count = 0;
	return ++count;
}

class task {
public:
	task(int data) : data_(data) {}
	auto lazy_launch()
	{
		return
			[*this, count = get_count()]()
			mutable {
				ostringstream oss;
				oss << "Done work " << data_
						<< " (No. " << count
						<< ") in thread "
						<< this_thread::get_id()
						<< '\n';
				msg_ = oss.str();
				calculate();
			};
	}
	void calculate()
	{
		this_thread::sleep_for(100ms);
		cout << msg_;
	}

private:
	int data_;
	string msg_;
};

map<string, function<int(int, int)>>
	op_dict{
		{"+",
		 [](int x, int y) {
			 return x + y;
		 }},
		{"-",
		 [](int x, int y) {
			 return x - y;
		 }},
		{"*",
		 [](int x, int y) {
			 return x * y;
		 }},
		{"/",
		 [](int x, int y) {
			 return x / y;
		 }},
	};
	
void example1() {
	cout << add_2(5) << endl;
	cout << add_22(5) << endl;
	cout << test1(add_22) << endl;
	cout << test2(add_22) << endl;
	cout << test3(&add_22) << endl;
	auto seven = adder(2)(5);
	cout << seven << endl;
	cout << [](int x) { return x * x; }(3) << endl;
}

int main()
{
	example1();
	auto t = task{37};
	thread t1{t.lazy_launch()};
	thread t2{t.lazy_launch()};
	t1.join();
	t2.join();
	
	array a{1,2,3,4,5};
	auto s = accumulate(a.begin(), a.end(), 1, [](auto x, auto y){
		return x * y;
	});
//	auto m = accumulate(a.begin(), a.end(), 0);
	cout << s << endl;
	cout << op_dict.at("+")(1,6) <<endl;
}

