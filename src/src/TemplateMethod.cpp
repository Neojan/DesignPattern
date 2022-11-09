#include <iostream>

using namespace std;

class TemplateMethod {
private:
    /* data */
protected:
    void Opreration1()
    {
        cout << "Opreration1" << endl;
    }
    virtual void Opreration2()
    {
        cout << "Opreration1" << endl;
    }
    void Opreration3()
    {
        cout << "Opreration3" << endl;
    }

public:
    void Run()
    {
        Opreration1();
        Opreration2();
        Opreration3();
    }
};

class ConcreteTemplateMethod : public TemplateMethod {
private:
    /* data */
protected:
    void Opreration2()
    {
        cout << "Concrete Opreration2" << endl;
    }
};

void TestTemplateMethod(void)
{
    TemplateMethod* test = new ConcreteTemplateMethod;
    test->Run();
    delete test;
}