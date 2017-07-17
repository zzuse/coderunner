#include <iostream>

using namespace std;
// Product

class AbstractProduct {
public:
    virtual ~AbstractProduct() { }
    virtual void Operation() = 0;
};

class ProductA :public AbstractProduct {
public:
    void Operation() {
        cout << "ProductA Operation" << endl;
    }
};

class ProductB :public AbstractProduct {
public:
    void Operation() {
        cout << "ProductB Operation" << endl;
    }
};

// Factory

class AbstractFactory {
public:
    virtual ~AbstractFactory() { }
    virtual AbstractProduct* CreateProductA() = 0;
    virtual AbstractProduct* CreateProductB() = 0;
};
//抽象工厂从实际工厂解耦,抽象工厂提供接口创建产品
//替换不同的工厂获得不同的行为
//抽象工厂利用工厂方法实现对象
//工厂方法用继承覆盖工厂方法
class ConcreteFactory :public AbstractFactory {
public:
    AbstractProduct* CreateProductA() {
        return new ProductA();
    }

    AbstractProduct* CreateProductB() {
        return new ProductB();
    }
};

int main() {
    AbstractFactory *factory = new ConcreteFactory();
    AbstractProduct* productA = factory->CreateProductA();
    AbstractProduct* productB = factory->CreateProductB();
    productA->Operation();
    productB->Operation();

    delete factory;
    delete productA;
    delete productB;

    return 0;
}