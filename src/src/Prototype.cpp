#include <iostream>
#include <cstring>

using namespace std;

// 关键词:Clone, 深拷贝

class Prototype {
private:
public:
    virtual ~Prototype() {}
    virtual Prototype* Clone() = 0;
    virtual void       Tell()  = 0;
};

class ConcretePrototypeA : public Prototype {
private:
    char* m_string;

public:
    ConcretePrototypeA(const char* data = 0)
    {
        if (data)
        {
            m_string = new char[strlen(data) + 1];
            strcpy(m_string, data);
        }
        else
        {
            m_string    = new char[1];
            m_string[0] = '\0';
        }
    }

    ConcretePrototypeA(ConcretePrototypeA& protoType)
    {
        m_string = new char[strlen(protoType.m_string) + 1];
        strcpy(m_string, protoType.m_string);
    }
    ~ConcretePrototypeA()
    {
        delete[] m_string;
    }
    virtual Prototype* Clone()
    {
        return new ConcretePrototypeA(*this);
    }
    void Tell()
    {
        cout << m_string << endl;
    }
};

class ConcretePrototypeB : public Prototype {
private:
    char* m_string;

public:
    ConcretePrototypeB(const char* data = 0)
    {
        if (data)
        {
            m_string = new char[strlen(data) + 1];
            strcpy(m_string, data);
        }
        else
        {
            m_string    = new char[1];
            m_string[0] = '\0';
        }
    }

    ConcretePrototypeB(ConcretePrototypeB& protoType)
    {
        m_string = new char[strlen(protoType.m_string) + 1];
        strcpy(m_string, protoType.m_string);
    }
    ~ConcretePrototypeB()
    {
        delete[] m_string;
    }
    virtual Prototype* Clone()
    {
        return new ConcretePrototypeB(*this);
    }
    void Tell()
    {
        cout << m_string << endl;
    }
};

enum PROTOTYPE_TYPE
{
    TYPEA   = 0,
    TYPEB   = 1,
    MAXTYPE = 2
} proType;

class ClientPrototype
{
private:
    static Prototype* m_prototype[MAXTYPE];

public:
    ~ClientPrototype()
    {
        for (unsigned int i = 0; i < MAXTYPE; i++)
        {
            if (m_prototype[i])
            {
                delete m_prototype[i];
            }
        }
    }
    static void Init()
    {
        if (!m_prototype[TYPEA])
        {
            m_prototype[TYPEA] = new ConcretePrototypeA("ConcretePrototypeA");
        }
        if (!m_prototype[TYPEB])
        {
            m_prototype[TYPEB] = new ConcretePrototypeB("ConcretePrototypeB");
        }
    }
    static Prototype* Make(PROTOTYPE_TYPE type)
    {
        if (type >= MAXTYPE)
        {
            return nullptr;
        }
        return m_prototype[type]->Clone();
    }
};

Prototype* ClientPrototype::m_prototype[MAXTYPE];


void TestPrototype(void)
{
    ClientPrototype client;
    client.Init();
    Prototype* a = client.Make(TYPEA);
    Prototype* b = client.Make(TYPEB);
    a->Tell();
    b->Tell();
    delete a;
    delete b;
}