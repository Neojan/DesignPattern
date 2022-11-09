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