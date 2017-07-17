#include <iostream>

using namespace std;

class Element;

class Visitor {
public:
    virtual ~Visitor();

    virtual void VisitConcreteElementA(Element* elm) = 0;
    virtual void VisitConcreteElementB(Element* elm) = 0;
protected:
    Visitor();
};

Visitor::Visitor() {
}

Visitor::~Visitor() {
}

//数据结构可以保持不变，数据的操作方式可不同
class Element {
public:
    Element();
    virtual ~Element();
    virtual void Accept(Visitor* vis) = 0;
};

Element::Element() {
}

Element::~Element() {
}

//增加新的元素类很困难,需在抽象访问者角色中增加一个新的抽象操作
//适用于数据结构相对稳定的系统
class ConcreteElementA :public Element {
public:
    void Accept(Visitor* vis);
};

class ConcreteElementB :public Element {
public:
    void Accept(Visitor* vis);
};

//双分派技术就是在选择一个方法的时候，
//不仅仅要根据消息接收者（receiver）的运行时区别（Run time type），还要根据参数的运行时区别。
//双分派意味着得到的执行操作决定于请求的种类和接受者的类型。
//但是违背了依赖倒置原则，这里具体实现将依赖具体实现
void ConcreteElementA::Accept(Visitor* vis) {
    vis->VisitConcreteElementA(this);
    cout << "visiting ConcreteElementA..." << endl;
}

void ConcreteElementB::Accept(Visitor* vis) {
    vis->VisitConcreteElementB(this);
    cout << "visiting ConcreteElementB..." << endl;
}


class ConcreteVisitorA :public Visitor {
public:
    void VisitConcreteElementA(Element* elm);
    void VisitConcreteElementB(Element* elm);
};

class ConcreteVisitorB :public Visitor {
public:
    void VisitConcreteElementA(Element* elm);
    void VisitConcreteElementB(Element* elm);
};

void ConcreteVisitorA::VisitConcreteElementA(Element* elm) {
    cout << "A will visit ConcreteElementA..." << endl;
}

void ConcreteVisitorA::VisitConcreteElementB(Element* elm) {
    cout << "A will visit ConcreteElementB..." << endl;
}

void ConcreteVisitorB::VisitConcreteElementA(Element* elm) {
    cout << "B will visit ConcreteElementA..." << endl;
}

void ConcreteVisitorB::VisitConcreteElementB(Element* elm) {
    cout << "B will visit ConcreteElementB..." << endl;

}

int main() {
    Visitor *vis = new ConcreteVisitorA();
    Element *elm = new ConcreteElementA();
    Element *elmb = new ConcreteElementB();
    Visitor *visb = new ConcreteVisitorB();
    elm->Accept(vis);
    elm->Accept(visb);
    elmb->Accept(visb);

    delete elm;
    delete vis;
    delete visb;

    return 0;
}