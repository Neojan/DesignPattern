## 动机
- 在软件系统采用纯粹对象方案的问题在于大量细粒度的对象会很快充斥在系统中 ， 从而带来很高的运行时代价一主要指内存需求方面的代价。
- 如何在避免大量细粒度对象问题的同时，让外部客户程序仍然能够透明地使用面向对象的方式来进行操作

## 模式定义
- 运用共享技术有效地支持大量细粒度的对象

## 结构

![在这里插入图片描述](./pics/%E4%BA%AB%E5%85%83%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
- 面向对象很好地解决了抽象性的问题，但是作为一个运行在机器中的程序实体，我们需要考虑对象的代价问题。Flyweight 主要解决面向对象的代价问题，一般不触及面向对象的抽象性问题
- Flyweight 采用对象共享的做法来降低系统中对象的个数，从而降低细粒度对象给系统带来的内存压力。在具体实现方面，要注意对象状态（最好状态不可更改）的处理
- 对象的数量太大从而导致对象内存开销加大 — 什么样的数量才算大？这需要我们仔细根据具体应用情况进行评估，而不能凭空臆断


## 代码

```cpp
#include <iostream>
#include <map>

using namespace std;

class Flyweight {
public:
    virtual void operation() = 0;
    virtual ~Flyweight(){};
};

class ConcreteFlyWeight1 : public Flyweight {
private:
    int m_state;

public:
    ConcreteFlyWeight1(int tstate)
        : m_state(tstate) {}
    void operation()
    {
        cout << m_state << endl;
    }
    ~ConcreteFlyWeight1(){};
};


class ConcreteFlyWeight2 : public Flyweight {
private:
    int m_state;

public:
    ConcreteFlyWeight2(int tstate)
        : m_state(tstate) {}
    void operation()
    {
        cout << m_state << endl;
    }
    ~ConcreteFlyWeight2(){};
};

class FlyweightFactory {
private:
    map<int, Flyweight*> m_flyweihts;

public:
    FlyweightFactory();
    Flyweight* GetFlyweight(int key);
    ~FlyweightFactory();
};

Flyweight* FlyweightFactory::GetFlyweight(int key)
{
    if (m_flyweihts.find(key) != m_flyweihts.end())
    {
        return m_flyweihts[key];
    }
    else
    {
        Flyweight* temp = new ConcreteFlyWeight1(key);
        m_flyweihts.insert(pair<int, Flyweight*>(key, temp));
        return temp;
    }
}

FlyweightFactory::FlyweightFactory()
{
}

FlyweightFactory::~FlyweightFactory()
{
    for (auto it = m_flyweihts.begin(); it != m_flyweihts.end(); it++)
    {
        delete it->second; //second means Flyweight*
    }
    m_flyweihts.clear();
}

void TestFlyweight()
{
    FlyweightFactory a;
    a.GetFlyweight(1)->operation();
    a.GetFlyweight(2)->operation();
}
```