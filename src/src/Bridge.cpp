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