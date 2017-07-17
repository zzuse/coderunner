#include <iostream>
#include <string>
#include <list>
using namespace std;

//独立的改变主题和观察者
class Subject;

//主题发生改变时定义一个更新接口，通知各观察者
class Observer {
public:
    virtual void Update(Subject* sub) = 0;
    virtual void PrintInfo() = 0;
    virtual ~Observer(){}
protected:
    Observer(){}
//    string _st;
};

//观察者模式定义了一个一对多的依赖关系
class Subject {
public:
    virtual void SetState(const string& st) = 0;
    virtual string GetState() = 0;
    virtual void Attach(Observer* obv){
        _obvs.push_front(obv);
    }
    virtual void Detach(Observer* obv){
        if (obv != nullptr) {
            _obvs.remove(obv);
        }
    }
    virtual void Notify(){
        for (auto obv : _obvs) {
            obv->Update(this);
        }
    }
    virtual ~Subject(){};
protected:
    Subject(){};
private:
    list<Observer*> _obvs;
};

//将有关状态存入各ConcreteSubject对象
class ConcreteSubject :public Subject {
public:
    string GetState(){
        return _st;
    }
    void SetState(const string& st){
        _st = st;
    }
private:
    string _st;
};

//observer的更新接口以使自身状态与主题的状态保持一致。
class ConcreteObserver :public Observer {
public:
    virtual Subject* GetSubject(){
        return _sub;
    }
    ConcreteObserver(Subject* sub){
        _sub = sub;
        _sub->Attach(this);
    }
    ~ConcreteObserver(){
        _sub->Detach(this);
    }

    void Update(Subject* sub){
        //_st = sub->GetState();
        sub->GetState();
        PrintInfo();
    }

    void PrintInfo(){
        cout << "ConcreteObserver::PrintInfo\t" << _sub->GetState() << endl;
    }
private:
    Subject *_sub;
};


int main() {
    Subject *sub = new ConcreteSubject();
    Observer *o1 = new ConcreteObserver(sub);
    Observer *o2 = new ConcreteObserver(sub);

    sub->SetState("old");
    sub->Notify();
    sub->SetState("new");
    sub->Notify();

    delete o1;
    delete o2;
    delete sub;

    return 0;
}
