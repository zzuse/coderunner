#include <iostream>
#include <string>
#include <vector>

using namespace std;

//某个类的一个实例能提供许多"虚拟"实例
//假如有个森林
//只用一个树实例和一个客户对象来维护"所有"树的状态
//又叫享元模式
//节省内存,区分内部变量和外部变量,
class Flyweight {
public:
    Flyweight(string state):_state(state) {

    }
    //内部,所有对象共享,由factory或manager管理
    virtual void Operation(const string&state) { }

    string GetState()const { return _state; }

    virtual ~Flyweight() { }
private:
    //外部,每个对象不同
    string _state;
};

class ConcreteFlyweight :public Flyweight {
public:
    ConcreteFlyweight(string state)
        :Flyweight(state) {
        cout << "ConcreteFlyweight Build..." << state << endl;
    }
    //内部变量可以以外部变量为参数
    void Operation(const string& state) {
        cout << "ConcreteFlyweight " << GetState() << " \\ " << state << endl;
    }
};

//专门维护外部状态的类
class FlyweightFactory {
public:
    Flyweight *GetFlyweight(std::string key) {
        for (auto fly : _flys) {
            if (fly->GetState() == key) {
                cout << "already created by users..." << endl;
                return fly;
            }
        }
        Flyweight *fn = new ConcreteFlyweight(key);
        _flys.push_back(fn);
        return fn;
    }
private:
    //虚拟对象集合,内部operation(),外部变量state
    std::vector<Flyweight*> _flys;
};

int main() {
    FlyweightFactory *fc = new FlyweightFactory();
    Flyweight *fw1 = fc->GetFlyweight("hello");
    Flyweight *fw2 = fc->GetFlyweight("world");
    Flyweight *fw3 = fc->GetFlyweight("hello");
    fw1->Operation("a");
    fw2->Operation("a");
    fw3->Operation("a");

    delete fw1;
    delete fw2;
    //delete fw3;
    delete fc;

    return 0;
}