#include <iostream>

using namespace std;

//提供一种方法访问一个容器（container）对象中各个元素
//这里aggregate就是容器，并且不暴露aggregate的细节
//在head first中是要实现iterator接口的hasNext()和next()方法
typedef int Object;
class Aggregate {
public:
    Aggregate();
    virtual ~Aggregate();
    //virtual Iterator* CreateIterator() = 0;
    virtual Object GetItem(int idx) = 0;
    virtual int GetSize() = 0;
};

class ConcreteAggreaget :public Aggregate {
public:
    enum { SIZE = 3 };
    ConcreteAggreaget();
    //Iterator* CreateIterator();
    Object GetItem(int idx);
    int GetSize();
private:
    Object _objs[SIZE];
};

class Iterator {
public:
    Iterator();
    virtual ~Iterator();
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual Object CurrentItem() = 0;
};

//在具体迭代器中保存了状态，比如_idx
class ConcreteIterator :public Iterator {
public:
    ConcreteIterator(Aggregate *ag, int idx /* = 0 */);

    void First();
    void Next();
    bool IsDone();
    Object CurrentItem();
private:
    Aggregate* _ag;
    int _idx;
};

Iterator::Iterator() {
}


Iterator::~Iterator() {
}

ConcreteIterator::ConcreteIterator(Aggregate *ag, int idx = 0) {
    _ag = ag;
    _idx = idx;
}

Object ConcreteIterator::CurrentItem() {
    return _ag->GetItem(_idx);
}

void ConcreteIterator::First() {
    _idx = 0;
}

void ConcreteIterator::Next() {
    if (_idx < _ag->GetSize()) {
        _idx++;
    }
}

bool ConcreteIterator::IsDone() {
    return (_idx == _ag->GetSize());
}

Aggregate::Aggregate() {
}

Aggregate::~Aggregate() {
}

ConcreteAggreaget::ConcreteAggreaget() {
    for (int i = 0; i < SIZE; i++) {
        _objs[i] = i;
    }
}

//Iterator* ConcreteAggreaget::CreateIterator() {
//    return new ConcreteIterator(this);
//}

Object ConcreteAggreaget::GetItem(int idx) {
    if (idx < this->GetSize()) {
        return _objs[idx];
    }
    else {
        return -1;
    }
}

int ConcreteAggreaget::GetSize() {
    return SIZE;
}

int main() {
    Aggregate* ag = new ConcreteAggreaget();
    Iterator *it = new ConcreteIterator(ag, 0);
    //这样写才能更说明问题 
    //Iterator iterator = collect.CreateIterator(); 
    for (; !(it->IsDone()); it->Next()) {
        cout << it->CurrentItem() << endl;
    }
    delete it;
    delete ag;

    return 0;
}