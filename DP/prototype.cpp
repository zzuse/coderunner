#include <iostream>
using namespace std;

// Prototype

class Prototype {
public:
    virtual Prototype* Clone() = 0;
    virtual ~Prototype() { }
};

class ConcretePrototype :public Prototype {
public:
    ConcretePrototype() { }
//复制构造函数，而此处又涉及到深复制和浅复制的问题
    ConcretePrototype(const ConcretePrototype&cp) {
        cout << "ConcretePrototype copy..." << endl;
    }
//通过复制现有实例来创建新实例
//动态抽取当前对象运行时的状态
    Prototype* Clone() {
        return new ConcretePrototype(*this);
    }
};

int main() {
    Prototype *prototype = new ConcretePrototype();
    cout << prototype << endl;
    Prototype* prototype1 = prototype->Clone();
    cout << prototype1 << endl;
    Prototype* prototype2 = prototype->Clone();
    cout << prototype2 << endl;

    delete prototype;
    delete prototype1;
    delete prototype2;

    return 0;
}