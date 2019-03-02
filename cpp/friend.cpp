#include <iostream>

using namespace std;

class Count
{
	friend void setX(Count &,int);
public:
	Count():x(0){}
	void print() const{
		cout << x << endl;
	}
private:
	int x;
};

void setX( Count &c,int val)
{
	c.x = val;
}

int main(int argc, char *argv[]) {
	Count counter;
	cout << "counter.x after instantiation: ";
	counter.print();
	
	setX(counter, 8);
	cout << "counter.x after call to setX friend function: ";
	counter.print();
}