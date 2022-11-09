#include <iostream>

using namespace std;

class SubsystemA {
public:
    void suboperation()
    {
        std::cout << "Subsystem A method" << std::endl;
        // ...
    }
    // ...
};

class SubsystemB {
public:
    void suboperation()
    {
        std::cout << "Subsystem B method" << std::endl;
        // ...
    }
    // ...
};

class SubsystemC {
public:
    void suboperation()
    {
        std::cout << "Subsystem C method" << std::endl;
        // ...
    }
    // ...
};

class Facade {
private:
    SubsystemA* subsystemA;
    SubsystemB* subsystemB;
    SubsystemC* subsystemC;
    // ...
public:
    Facade()
    {
        subsystemA = new SubsystemA();
        subsystemB = new SubsystemB();
        subsystemC = new SubsystemC();
    }
    ~Facade()
    {
        delete subsystemA;
        delete subsystemB;
        delete subsystemC;
    }

    void operation1()
    {
        subsystemA->suboperation();
        subsystemB->suboperation();
        // ...
    }

    void operation2()
    {
        subsystemC->suboperation();
        // ...
    }
    // ...
};


void TestFacade(void)
{
    Facade* facade = new Facade();
    facade->operation1();
    facade->operation2();
    delete facade;
}