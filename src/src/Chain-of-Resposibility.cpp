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