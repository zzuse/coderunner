#include <iostream>

using namespace std;
class A {
	public:
		A() {cout << "Create A\n";}
		~A() { cout << "Destroy A\n";}
		A(const A&) {cout << "Copy A\n";}
		A(A&&) {cout << "Move A\n";}
//		A(A&&) = delete;
};

A getA_unnamed()
{
	return A();
}

A getA_named(){
	A a;
	return a;
}

// 编译器返回值优化被难倒了
A getA_duang()
{
	A a1;
	A a2;
	if (rand()>42) {
		return a1;
	} else {
		return a2;
	}
}

int main(int argc, char *argv[]) {
	auto a = getA_duang();
}