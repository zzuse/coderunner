#include <iostream>
using namespace std;

class Reciever {
public:
    void Action() {
        cout << "Reciever::Action..." << endl;
    }
};

class Command {
public:
    virtual ~Command() { }
    virtual void Excute() = 0;
};

class ConcreteCommand :public Command {
public:
    ConcreteCommand(Reciever *rev) {
        _rev = rev;
    }

    void Excute() {
        _rev->Action();
    }
private:
    Reciever *_rev;
};

//命令模式将"请求"封装成对象,以便使用不同的请求,队列或者日志来参数化其他对象.
//命令模式把发出命令的责任和执行命令的责任分割开，委派给不同的对象。
//Open to command, Close to Invoker
//深化:可以容易地实现对请求的Undo和Redo
class Invoker {
public:
    Invoker(Command* cmd) {
        _cmd = cmd;
    }
    void Invoke() {
        _cmd->Excute();
    }

private:
    Command *_cmd;
};

int main() {
    Reciever *rev = new Reciever();
    Command* cmd = new ConcreteCommand(rev);
    Invoker *inv = new Invoker(cmd);
    inv->Invoke();

    delete rev;
    delete cmd;
    delete inv;

    return 0;
}