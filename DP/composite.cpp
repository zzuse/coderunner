#include <iostream>
#include <vector>
using namespace std;

//组合模式有两个责任,1,管理层次结构.2,提供operation操作.典型的折中案例
//为页节点和组合节点提供共同的接口
class Component {
public:
    virtual void Operation() { }

    virtual void Add(const Component& com) { }

    virtual void Remove(const Component& com) { }

    virtual Component* GetChild(int index) {
        return 0;
    }

    virtual ~Component() { }
};

//定义一些容器类来存储这些简单对象
//某种树形结构,可以容纳菜单,子菜单
//使得用户对单个对象和组合对象的使用具有一致性。
class Composite :public Component {
public:
    void Add(Component* com) {
        _coms.push_back(com);
    }

    void Operation() {
        for (auto com : _coms)
            com->Operation();
    }

    void Remove(Component* com) {
        //_coms.erase(&com);
    }

    Component* GetChild(int index) {
        return _coms[index];
    }
private:
    //任意数量的孩子
    std::vector<Component*> _coms;
};

class Leaf :public Component {
public:
    void Operation() {
        cout << "Leaf::Operation..." << endl;
    }
};


int main() {
    Leaf *leaf = new Leaf();
    leaf->Operation();
    Composite *com = new Composite();
    com->Add(leaf);
    com->Operation();
    Component *leaf_ = com->GetChild(0);
    leaf_->Operation();

    delete leaf;
    delete com;

    return 0;
}