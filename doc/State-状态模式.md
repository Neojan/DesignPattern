## 动机
* 在软件构建过程中，某些对象的状态如果改变，其行为也会随之而发生变化，比如文档处于只读状态，其支持的行为和读写状态支持的行为可能完全不同
* 如何在运行时根据对象的状态来透明地更改对象的行为，而不会为对象操作和状态转换之间引入紧耦合？

## 模式定义
* 允许一个对象在其内部状态改变时改变它的行为，从而使对象看起来似乎修改了其行为
* 
## 结构
![](./pics/%E7%8A%B6%E6%80%81%E6%A8%A1%E5%BC%8F.jpeg)
## 要点
* State 模式将所有与一个特定状态相关的行为都放入一个 State 的子类对象中，在对象状态切换时，切换相应的对象；但同时维持 State 的接口，这样实现了具体操作与状态转换之间的解耦
* 为不同的状态引入不同的对象使得状态转换变得更加明确，而且可以保证不会出现状态不一致的情况，因为转换是原子性的 — 即要么彻底转换过来，要么不转换
* 如果 State 对象没有实例变量，那么各个上下文可以共享同一个 State 对象，从而节省对象开销


## 代码

```cpp
#include <iostream>

using namespace std;

class State {
private:
public:
    virtual ~State() {}
    virtual void operation1() = 0;
    virtual void operation2() = 0;
};

class ConcreteState1 : public State {
private:
    /* data */
public:
    ConcreteState1(/* args */);
    ~ConcreteState1();
    void operation1()
    {
        cout << "ConcreteState1 operation1" << endl;
    }
    void operation2()
    {
        cout << "ConcreteState1 operation2" << endl;
    }
};

ConcreteState1::ConcreteState1(/* args */)
{
}

ConcreteState1::~ConcreteState1()
{
}

class ConcreteState2 : public State {
private:
    /* data */
public:
    ConcreteState2(/* args */);
    ~ConcreteState2();
    void operation1()
    {
        cout << "ConcreteState2 operation1" << endl;
    }
    void operation2()
    {
        cout << "ConcreteState2 operation2" << endl;
    }
};

ConcreteState2::ConcreteState2(/* args */)
{
}

ConcreteState2::~ConcreteState2()
{
}

class Context {
private:
    State* m_state;

public:
    Context(){};
    ~Context();
    void setState(State* state)
    {
        if (m_state)
        {
            delete m_state;
        }
        m_state = state;
    }
    void Handle()
    {
        if (m_state)
            m_state->operation1();
    }
};


Context::~Context()
{
    delete m_state;
}


void TestState()
{
    Context* context = new Context();
    context->setState(new ConcreteState1());
    context->Handle();
    context->setState(new ConcreteState2());
    context->Handle();
    delete context;
}
```
