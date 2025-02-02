## 动机
* 在软件构建过程中，一个请求可能被多个对象处理，但是每个请求在运行时只能有一个接受者；如果显示指定，将不可避免地带来发送者和接受者的紧耦合
* 如何使请求的发送者不需要指定具体的接受者，让请求的接受者自己在运行时决定来处理请求，从而使两者解耦？

## 模式定义
使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递请求，知道有一个对象处理它为止

## 结构

![在这里插入图片描述](./pics/%E8%B4%A3%E4%BB%BB%E9%93%BE%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
* 责任链模式的应用场合在于“一个请求可能有多个接收者，但是最后真正的接收者只有一个”，这时候请求的发送者与接收者的耦合可能出现“变化脆弱”的症状，职责链的目的就是将二者解耦，从而更好地应对变化
* 应用了职责链模式后，对象的职责分派将更具有灵活性。我们可以在运行时动态添加/修改请求的处理职责
* 如果请求传递到职责链的末尾仍得不到处理，应该有一个合理的缺省机制。这也是每一个接收者的责任，而不是发出请求的对象的责任
* 例子：多级审批流程（员工→经理→CEO）。Approver抽象类定义setNext()和approve()，Manager、Director、CEO构成审批链。

## 代码

```cpp
#include <iostream>

using namespace std;

enum REQUEST_TYPE
{
    REQUEST_TYPE1,
    REQUEST_TYPE2,
    REQUEST_TYPE3
};

class Request {
private:
    string       m_msg;
    REQUEST_TYPE m_type;

public:
    Request(const string& msg, REQUEST_TYPE type)
        : m_msg(msg), m_type(type) {}
    ~Request() {}
    REQUEST_TYPE GetRequestType() const
    {
        return m_type;
    }
    const string& GetRequestMsg() const
    {
        return m_msg;
    }
};

class ChainHandler {
private:
    ChainHandler* m_nextHandler;

protected:
    virtual bool CanHandleRequest(const Request& req) = 0;
    virtual bool HandleRequest(const Request& req)    = 0;

public:
    ChainHandler()
    {
        m_nextHandler = nullptr;
    }
    virtual ~ChainHandler() {}
    void SetNextChain(ChainHandler* next)
    {
        m_nextHandler = next;
    }
    void SendRequestToNext(const Request& req)
    {
        if (m_nextHandler != nullptr)
        {
            m_nextHandler->HandleRequest(req);
        }
    }
    void Handle(const Request& req)
    {
        if (CanHandleRequest(req))
        {
            HandleRequest(req);
        }
        else
        {
            SendRequestToNext(req);
        }
    }
};

class ConcreteChainHandler1 : public ChainHandler {
protected:
    bool CanHandleRequest(const Request& req)
    {
        return req.GetRequestType() == REQUEST_TYPE1;
    }
    bool HandleRequest(const Request& req)
    {
        cout << "ConcreteChainHandler1 " << req.GetRequestMsg() << endl;
    }
};

class ConcreteChainHandler2 : public ChainHandler {
protected:
    bool CanHandleRequest(const Request& req)
    {
        return req.GetRequestType() == REQUEST_TYPE2;
    }
    bool HandleRequest(const Request& req)
    {
        cout << "ConcreteChainHandler2 " << req.GetRequestMsg() << endl;
    }
};

class ConcreteChainHandler3 : public ChainHandler {
protected:
    bool CanHandleRequest(const Request& req)
    {
        return req.GetRequestType() == REQUEST_TYPE3;
    }
    bool HandleRequest(const Request& req)
    {
        cout << "ConcreteChainHandler3 " << req.GetRequestMsg() << endl;
    }
};

void TestChainOfResposibility(void)
{
    Request               req("Process request", REQUEST_TYPE3);
    ConcreteChainHandler1 h1;
    ConcreteChainHandler2 h2;
    ConcreteChainHandler3 h3;
    h1.SetNextChain(&h2);
    h2.SetNextChain(&h3);

    h1.Handle(req);
}
```