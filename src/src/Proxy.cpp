#include <iostream>

using namespace std;

class ISubject {
public:
    virtual ~ISubject(){}
    virtual void Request() = 0;
};

class RawSubject : public ISubject {
public:
    ~RawSubject() {}
    void Request()
    {
        cout << "RawSubject operation" << endl;
    }
};

class Proxy : public ISubject {
private:
    RawSubject* m_rawSubject;

public:
    Proxy()
    {
        //组合了RawSubject
        m_rawSubject = new RawSubject();
    }
    ~Proxy()
    {
        delete m_rawSubject;
    }
    void Request()
    {
        m_rawSubject->Request();
    }
};

void
TestProxy(void)
{
    Proxy* proxy = new Proxy();
    proxy->Request();
    delete proxy;
}