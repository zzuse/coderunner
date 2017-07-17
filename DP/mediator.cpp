#include <iostream>
#include <string>
using namespace std;

//集中相关对象之间的复杂沟通和控制方式
//每个对象改变时把状态告诉中介者
//每个对象都会对中介者请求做出回应
//对象之间彻底解耦
//缺点：“中介“承担了较多的责任
class Person;

class Mediator {
public:
    virtual void Send(const string& msg, Person* person) = 0;

    virtual ~Mediator() { }

    void BuildRelation(Person *a, Person *b) {
        m_a = a;
        m_b = b;
    }

protected:
    Person *m_a;
    Person *m_b;
};

//从具体同事接收消息，向具体同事对象发出命令
class ConcreteMediator :public Mediator {
public:
    void Send(const string& msg, Person* person) {
        if (person == m_a) {
            cout << msg << "--Mediator--PersonB" << endl;
        }
        else if (person == m_b) {
            cout << msg << "--Mediator--PersonA" << endl;
        }
    }
};

class Person {
public:
    Person(Mediator*md):_md(md) { }
    virtual void SendMessage(const string& msg) = 0;
    virtual ~Person() { }
protected:
    Mediator* _md;
};

//只知道自己的行为，都认识中介者对象
class ConcretePersonA :public Person {
public:
    ConcretePersonA(Mediator* md):Person(md) { }

    void SendMessage(const string& msg) {
        _md->Send(msg, this);
    }

};

class ConcretePersonB :public Person {
public:
    ConcretePersonB(Mediator* md):Person(md) { }

    void SendMessage(const string& msg) {
        _md->Send(msg, this);
    }
};

int main() {
    Mediator *mediator = new ConcreteMediator();
    Person *personA = new ConcretePersonA(mediator);
    Person *personB = new ConcretePersonB(mediator);

    mediator->BuildRelation(personA, personB);
    personA->SendMessage("PersonAs");
    personB->SendMessage("PersonBs");

    delete personA;
    delete personB;
    delete mediator;

    return 0;
}