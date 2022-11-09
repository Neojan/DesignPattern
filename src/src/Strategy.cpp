#include <iostream>

using namespace std;

class Strategy {
private:
    /* data */
public:
    virtual void AlgorithmInterface()
    {
        cout << "Defaul algorithm" << endl;
    }
};

class ConcreteStrategyA : public Strategy {
private:
    /* data */
public:
    void AlgorithmInterface()
    {
        cout << "ConcreteStrategyA algorithm" << endl;
    }
};

class ConcreteStrategyB : public Strategy {
private:
    /* data */
public:
    void AlgorithmInterface()
    {
        cout << "ConcreteStrategyB algorithm" << endl;
    }
};

class ConcreteStrategyC : public Strategy {
private:
    /* data */
public:
    void AlgorithmInterface()
    {
        cout << "ConcreteStrategyC algorithm" << endl;
    }
};

class ContextStrategy {
private:
    Strategy* m_strategy;

public:
    ContextStrategy(Strategy* const strategy)
        : m_strategy(strategy)
    {
    }
    ~ContextStrategy()
    {
        delete m_strategy;
    }
    void ContextStrategyInterface()
    {
        m_strategy->AlgorithmInterface();
    }
};

void TestStrategy(void)
{
    ContextStrategy context(new ConcreteStrategyA());
    context.ContextStrategyInterface();
}