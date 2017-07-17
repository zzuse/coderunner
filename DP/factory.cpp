#include <iostream>
using namespace std;

// Product

class Product {
public:
    virtual ~Product() { }
    virtual void say() = 0;
};

class ConcreteProduct :public Product {
public:
    ConcreteProduct() {
        std::cout << "ConcreteProduct..." << std::endl;
    }
    void say() {
        std::cout << "ConcreteProduct Say..." << std::endl;
    }
    ~ConcreteProduct() { }
};

// Factory

class Factory {
public:
    virtual Product* CreateProduct() = 0;
    virtual ~Factory() { }
protected:
    Factory() { }
};

class ConcreteFactory :public Factory {
public:
    ConcreteFactory() {
        std::cout << "ConcreteFactory..." << std::endl;
    }

    ~ConcreteFactory() {

    }
//选择哪个工厂子类,自然就决定了创建的产品是哪个
//增加或改变产品,creator不受影响
//如果不使用继承而是通过类型来指定产品,那就是简单工厂,
//简单工厂不是一种设计模式,而是一种编程封装习惯
    Product* CreateProduct() {
        return new ConcreteProduct();
    }

};

// Test

int main() {
    Factory *factory = new ConcreteFactory();
    Product *product = factory->CreateProduct();
    product->say();

    delete factory;
    delete product;

    return 0;
}
