#include <iostream>
#include <memory>
#include <utility>
using namespace std;

class shape {
public:
	virtual ~shape() {}
};

class circle : public shape {
public:
	circle() { puts("circle()"); }
	~circle() { puts("~circle()"); }
};

class triangle : public shape {
public:
	triangle() { puts("triangle()"); }
	~triangle() { puts("~triangle()"); }
};

class result {
public:
	result() { puts("result()"); }
	~result() { puts("~result()"); }
};

result
process_shape(const shape& shape1,
							const shape& shape2)
{
	puts("process_shape()");
	return result();
}

void foo(const shape&){
	puts("foo(const shape&)");
}
void foo(shape&&){
	puts("foo(shape&&)");
}

template <typename T>
void bar(T&& s)
{
	foo(std::forward<T>(s));
}


//void bar(const shape& s){
//	puts("bar(const shape&)");  
//	foo(s);
//}
//void bar(shape&& s){  
//	puts("bar(shape&&)");  
//	foo(std::move(s));
//}


class Obj {
public:
	Obj()
	{
		cout << "Obj()" << endl;
	}
	Obj(const Obj&)
	{
		cout << "Obj(const Obj&)"
			 << endl;
	}
	Obj(Obj&&)
	{
		cout << "Obj(Obj&&)" << endl;
	}
};

Obj simple()
{
	Obj obj;
	//  简单返回对象；一般有  NRVO
	return obj;
}

Obj simple_with_move()
{
	Obj obj;
	// move  会禁止  NRVO
	return std::move(obj);
}

Obj complicated(int n)
{
	Obj obj1;
	Obj obj2;
	//  有分支，一般无  NRVO
	if (n % 2 == 0) {
		return obj1;
	} else {
		return obj2;
	}
}

int obj_test()
{
	cout << "*** 1 ***" << endl;
	auto obj1 = simple();
	cout << "*** 2 ***" << endl;
	auto obj2 = simple_with_move();
	cout << "*** 3 ***" << endl;
	auto obj3 = complicated(42);
	return 0;
}



int main(){
//	puts("main()");
//	process_shape(circle(), triangle());
//	puts("something else");

	bar(circle());
	return 0;
}