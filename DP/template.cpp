#include <iostream>
using namespace std;

//不变的行为搬移到超类，去除了子类中的重复代码
//Template methods use inheritance to vary part of an algorithm. 
//Strategies use delegation to vary the entire algorithm
class AbstractClass {
public:
    virtual void TemplateMethod() {
        PrimitiveOperation1();
        PrimitiveOperation2();
    }

    virtual ~AbstractClass() { }
protected:
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;
    AbstractClass() { }
};

class ConcreteClass1 :public AbstractClass {
public:
    void PrimitiveOperation1() {
        cout << "ConcreteClass1::PrimitiveOperation1" << endl;
    }

    void PrimitiveOperation2() {
        cout << "ConcreteClass1::PrimitiveOperation2" << endl;
    }
};

class ConcreteClass2 :public AbstractClass {
public:
    void PrimitiveOperation1() {
        cout << "ConcreteClass2::PrimitiveOperation1" << endl;
    }

    void PrimitiveOperation2() {
        cout << "ConcreteClass2::PrimitiveOperation2" << endl;
    }
};



int main() {
    AbstractClass *p1 = new ConcreteClass1();
    AbstractClass *p2 = new ConcreteClass2();
    p1->TemplateMethod();
    p2->TemplateMethod();

    delete p1;
    delete p2;

    return 0;
}