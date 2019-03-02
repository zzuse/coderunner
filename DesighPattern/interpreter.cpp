#include <iostream>
#include <string>
using namespace std;

//这个角色的任务一般是用来存放文法中各个终结符所对应的具体值，
//比如R=R1+R2，我们给R1赋值100，给R2赋值200。
//这些信息需要存放到环境角色中，很多情况下我们使用Map来充当环境角色就足够了。
//环境角色还可以做表达式的前中后序遍历，将expresstion层层封装，最后暴露一个非终结表达式
//非终结表达式通过递归最终将表达式的值获取，终结表达式中的变量可以通过hash_map来设定
class Context { };
//为执行operation()声明一个接口
class Expression {
public:
    virtual ~Expression() { }
    virtual void Interpret(const Context& c) = 0;
};

//终结符解释器
class TerminalExpression :public Expression {
public:
    TerminalExpression(const string& statement) {
        _statement = statement;
    }

    void Interpret(const Context& c) {
        cout << this->_statement << " -- TerminalExpression" << endl;
    }

private:
    string _statement;
};

//非终结符解释器
class NonterminalExpression :public Expression {
public:
    NonterminalExpression(Expression* expression, int times) {
        _expression = expression;
        _times = times;
    }

    void Interpret(const Context& c) {
        for (int i = 0; i < _times; i++) {
            _expression->Interpret(c);
        }
    }

private:
    Expression *_expression;
    int _times;
};

int main() {
    Context *c = new Context();
    Expression *tp = new TerminalExpression("echo");
    Expression *ntp = new NonterminalExpression(tp, 4);
    ntp->Interpret(*c);

    delete ntp;
    delete tp;
    delete c;

    return 0;
}

