## 动机
- 在软件系统中，经常面临着“ 某些结构复杂的对象 ”的创建工作；由于需求的变化，这些对象经常面临着剧烈的变化，但是它们却拥有比较稳定一致的接口
- 如何应对这种变化，如何向“客户程序（使用这些对象的程序）”隔离出“这些易变对象”，从而使得“依赖这些易变对象的客户程序”不随着需求改变而改变？

## 模式定义
使用原型实例指定创建对象的种类，然后通过拷贝这些原型来创建新的对象

## 结构

![在这里插入图片描述](./pics/%E5%8E%9F%E5%9E%8B%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
- Prototype 模式同样用于隔离类对象的使用者和具体类型（易变类）之间的耦合关系，它同样要求这些“易变类”拥有“稳定的接口”
- Prototype 模式对于“如何创建易变类的实体对象”采用“原型克隆”的方法来做，使得我们可以非常灵活地动态创建“拥有某些稳定接口”的新对象 — 所需工作仅仅是注册一个新类的对象（即原型），然后在任何需要的地方 clone
- Prototype 模式中的 clone 方法可以利用某些框架中的序列化来实现深拷贝

## 代码

```cpp
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
```