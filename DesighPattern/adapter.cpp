
#include <iostream>
using namespace std;

class Target {
public:
    virtual void Request() {
        cout << "Target::Request..." << endl;
    }
    virtual ~Target() { }
};

class Adaptee {
public:
    void SpecificRequest() {
        cout << "Adaptee::SpecificRequest..." << endl;
    }
};
//类适配器需要多重继承(java无法使用),对象适配器不需要多重继承(而使用组合)
//类适配器需要伪装什么方法,就覆盖什么方法,不需要都重新实现,高效
//对象适配器则可以适配任何子类,灵活
class Adapter :public Target, private Adaptee {
public:
    Adapter(Adaptee* ade) {
        _ade = ade;
    }
    void Request() {
        _ade->SpecificRequest();
    }
private:
    Adaptee *_ade;
};

int main() {
    Adaptee *adaptee = new Adaptee();
    Target *adapter = new Adapter(adaptee);

    adapter->Request();

    delete adapter;
    delete adaptee;

    return 0;
}