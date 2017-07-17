#include <iostream>
using namespace std;

//每个状态的行为局部化到自己的类中
//内部状态改变时，则改变行为，看起来像修改了它的类，实际上是使用组合引用了不同状态对象
class State;
class ConcreteStateB;
class ConcreteStateA;

class Context {
public:
    Context(State* st);
    void OperationInterface();
    void OperationChangeState();
private:
    friend class State;
    bool ChangeState(State* st);
    State *_st;
};

class State {
public:
    virtual void OperationChangeState(Context*) = 0;
    virtual void OperationInterface(Context*) = 0;
    virtual ~State() { }
protected:
    //状态通过上下文改变到下一个状态，这里有点像链式，
    //状态由上下文来控制管理
    //所以我感觉最好的方法不是由State本身传入下一个状态，而是上下文暴露get()方法
    //如context.getXXXstate()，由每个子类自己定义
    bool ChangeState(Context* con, State *st) {
        con->ChangeState(st);
    }
};

class ConcreteStateB :public State {
public:
    void OperationChangeState(Context* con);
    void OperationInterface(Context* con);
};

class ConcreteStateA :public State {
public:
    void OperationChangeState(Context* con) {
        OperationInterface(con);
        this->ChangeState(con, new ConcreteStateB());
    }

    void OperationInterface(Context* con) {
        cout << "ConcreteStateA::OperationInterface..." << endl;
    }
};

void ConcreteStateB::OperationChangeState(Context* con) {
    OperationInterface(con);
    this->ChangeState(con, new ConcreteStateA());
}

void ConcreteStateB::OperationInterface(Context* con) {
    cout << "ConcreteStateB::OperationInterface..." << endl;
}

Context::Context(State* st) {
    _st = st;
}

void Context::OperationInterface() {
    _st->OperationInterface(this);
}

void Context::OperationChangeState() {
    _st->OperationChangeState(this);
}

bool Context::ChangeState(State* st) {
    _st = st;
    return true;
}

int main() {
    State *st = new ConcreteStateA();
    Context *con = new Context(st);
    //不断请求Request();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();

    delete con;
    delete st;

    return 0;
}