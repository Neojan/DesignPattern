## 动机
- 由于某些类型的固有的实现逻辑，使得它们具有两个变化的维度，乃至多个纬度的变化。
- 如何应对这种“多维度的变化”？如何利用面向对象技术来使得类型可以轻松地沿着两个乃至多个方向变化，而不引入额外的复杂度？

## 模式定义
将抽象部分(业务功能)与实现部分(平台实现)分离，使它们都可以独立地变化。——《设计模式》GoF

## 结构

![在这里插入图片描述](./pics/%E6%A1%A5%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
- Bridge模式使用“对象间的组合关系”解耦了抽象和实现之间固有的绑定关系，使得抽象和实现可以沿着各自的维度来变化。所谓抽象和实现沿着各自纬度的变化，即“子类化”它们。
- Bridge模式有时候类似于多继承方案，但是多继承方案往往违背单一职责原则（即一个类只有一个变化的原因），复用性比较差。Bridge模式是比多继承方案更好的解决方法。
- Bridge模式的应用一般在“两个非常强的变化维度”，有时一个类也有多于两个的变化维度，这时可以使用Bridge的扩展模式。

## 应用
桥接模式其它应用场景：
- 对于那些不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统，桥接模式尤为适用.
- 常见的应用场景:
- JDBC驱动程序：java中统一api访问多种数据库（Mysql，Orange，SQL等）。桥模式和策略模式不冲突
- 银行转账系统
    转账分类: 网上转账，柜台转账，AMT转账
    转账用户类型：普通用户，银卡用户，金卡用户..
- 消息管理
    消息类型：即时消息，延时消息
    消息分类：手机短信，邮件消息，QQ消息...
- 多维度变化的图形渲染（如形状+颜色组合）。Shape抽象类持有Color接口引用，Circle和RedColor可独立扩展

## 桥接模式与装饰者模式的区别
桥接模式的定义是将抽象化与实现化分离（用组合的方式而不是继承的方式），使得两者可以独立变化。可以减少派生类的增长。这样看起来和装饰者差不多，但两者还是有一些比较重要的区别：

- 桥接模式中所说的分离，其实是指将结构与实现分离（当结构和实现有可能发生变化时）或属性与基于属性的行为进行分离；而装饰者只是对基于属性的行为进行封闭成独立的类。

- 桥接中的行为是横向的行为，行为彼此之间无关联；而装饰者模式中的行为具有可叠加性，其表现出来的结果是一个整体，一个各个行为组合后的一个结果。

## 代码

```cpp
#include <iostream>

using namespace std;

class Implementor {
public:
    virtual ~Implementor() {}
    virtual void OperationImp() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    ~ConcreteImplementorA() {}
    void OperationImp()
    {
        cout << "ConcreteImplementorA" << endl;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    ~ConcreteImplementorB() {}
    void OperationImp()
    {
        cout << "ConcreteImplementorB" << endl;
    }
};

class Abstraction {
public:
    virtual ~Abstraction()
    {
    }
    virtual void Operation() = 0;
};

class RefinedAbstraction : public Abstraction {
private:
    Implementor* m_implementor;

public:
    RefinedAbstraction(Implementor* implementor)
        : m_implementor(implementor) {}
    ~RefinedAbstraction()
    {
    }
    void Operation()
    {
        m_implementor->OperationImp();
    }
};

void TestBridge(void)
{
    Implementor* ia = new ConcreteImplementorA;
    Implementor* ib = new ConcreteImplementorB;

    Abstraction* abstract1 = new RefinedAbstraction(ia);
    abstract1->Operation();

    Abstraction* abstract2 = new RefinedAbstraction(ib);
    abstract2->Operation();

    delete abstract1;
    delete abstract2;

    delete ia;
    delete ib;
}
```
