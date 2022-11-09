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