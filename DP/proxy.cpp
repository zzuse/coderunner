#include <iostream>
using namespace std;

class Subject {
public:
    virtual void Request() = 0;
    virtual ~Subject() { }
};

class ConcreteSubject :public Subject {
public:
    void Request() {
        cout << "ConcreteSubject::Request..." << endl;
    }
};
//代理就是代表某个真实的对象，可以是存在同一个堆中，也可以通过封装网络调用，实现远程调用
//此处的代理是本地调用，也可以叫虚拟代理
//还有种叫虚拟代理，比如在subject还未准备好的时候，显示进度条
//无论是哪种代理，都是将客户端对subject的调用拦截下来，控制对象的访问
//间接的做一些事情如（做大对象的代表，保护，远程调用，缓存池）
//代理太多了，像个动物园（防火墙代理，缓存代理，智能引用代理，同步代理，写入时复制代理，复杂隐藏代理，动态）
//动态代理是不需要定义代理角色见DynamicProxyClient.java
class Proxy {
public:
    Proxy(Subject* subject) {
        _sub = subject;
    }

    void Reuqest() {
        cout << "Proxy::Request..." << endl;
        _sub->Request();
    }

private:
    Subject *_sub;
};

int main() {
    Subject *sub = new ConcreteSubject();
    Proxy *p = new Proxy(sub);
    p->Reuqest();

    delete sub;
    delete p;

    return 0;
}