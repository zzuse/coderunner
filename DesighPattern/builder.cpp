#include <iostream>
using namespace std;

// Product

class Product {
public:
    Product() {
        cout << "Product..." << endl;
    }
};

// Builder
//KFC场景 食品这些在不同的儿童餐中可以是不同的，但是组合成儿童餐的过程是相同的
//变的部分是复杂对象中各个子部件实现
//由具体生成器生成的产品，它们的表示相差如此之大以至于给不同的产品以公共父类没有太大必要
//实现产品构建和产品表现的分离
//生成器模式的重心还是在于分离整体构建算法与子部件的构建，
//分步骤构建对象只不过是整体构建算法一个简单表现，或者说是一个附带产物。
class Builder {
public:
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual Product* GetProduct() = 0;
    virtual ~Builder() { }
};

class ConcreteBuilder :public Builder {
public:
    void BuildPartA() {
        cout << "BuildPartA..." << endl;
    }

    void BuildPartB() {
        cout << "BuildPartB..." << endl;
    }

    void BuildPartC() {
        cout << "BuildPartC..." << endl;
    }

    Product* GetProduct() {
        return new Product();
    }
};

// Director

class Director {
public:
    Director(Builder* pBuilder) {
        _builer = pBuilder;
    }

    void Construct() {
        _builer->BuildPartA();
        _builer->BuildPartB();
        _builer->BuildPartC();
    }

private:
    Builder *_builer;
};


int main() {
    auto builder = new ConcreteBuilder();
    auto director = new Director(builder);
    director->Construct();
    Product* product = builder->GetProduct();

    delete product;
    delete builder;
    delete director;

    return 0;
}