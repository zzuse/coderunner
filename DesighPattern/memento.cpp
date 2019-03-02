#include <iostream>
#include <string>
using namespace std;

//专门掌握状态的对象就叫备忘录
//防止Originator以外对象访问
//备忘录对象，保存一个状态
class Memento {
private:
    friend class Originator;
    Memento(const string& st) {
        _st = st;
    }
    void SetState(const string& st) {
        _st = st;
    }
    string GetState() {
        return _st;
    }
private:
    string _st;
};

//此例子无备忘录管理者类
//管理者类可以管理多个Memento对象甚至组成数组来管理，
//只有一个Memento的时候可以忽略此类，如果有多个状态则需要管理者

//发起者对象
class Originator {
public:
    Originator() {
        _mt = nullptr;
    }

    Originator(const string &st) {
        _st = st;
        _mt = nullptr;
    }

    Memento* CreateMemento() {
        return new Memento(_st);
    }

    void SetMemento(Memento* mt) {
        _mt = mt;
    }

    void RestoreToMemento(Memento* mt) {
        _st = mt->GetState();
    }

    string GetState() {
        return _st;
    }

    void SetState(const string& st) {
        _st = st;
    }

    void PrintState() {
        cout << _st << "..." << endl;
    }

private:
    string _st;
    Memento *_mt;
};

int main() {
    Originator *o = new Originator();
    o->SetState("old");
    o->PrintState();
    Memento *m = o->CreateMemento();
    o->SetState("new");
    o->PrintState();
    o->RestoreToMemento(m);
    o->PrintState();

    delete o;
    delete m;

    return 0;
}