#include <iostream>

using namespace std;

class Target {
public:
    virtual ~Target() {}
    virtual void Request() = 0;
};

class Adaptee {
public:
    ~Adaptee() {}
    void SpecificRequest()
    {
        cout << "SpecificRequest" << endl;
    }
};

//Object Adapter
class Adapter1 : public Target {
private:
    Adaptee* m_adaptee;

public:
    Adapter1()
    {
        m_adaptee = new Adaptee();
    }
    ~Adapter1()
    {
        delete m_adaptee;
    }
    void Request()
    {
        m_adaptee->SpecificRequest();
    }
};

//Class Adapter
class Adapter2 : public Target, private Adaptee {
public:
    virtual void Request()
    {
        SpecificRequest();
    }
    // ...
};


void TestAdapter(void)
{
    Target* t1 = new Adapter1();
    t1->Request();
    delete t1;

    Target* t2 = new Adapter2();
    t2->Request();
    delete t2;
}