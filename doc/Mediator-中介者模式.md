## 动机
- 在软件构建过程中，经常会出现多个对象互相关联交互的情况，对象之间常常会维持一种复杂的引用关系，如果遇到一些需求的更改，这种直接的引用关系将会面临不断的变化
- 在这种情况下，我们可以使用一个“中介对象”来关系对象间的关联关系，避免相互交互的对象之间的紧耦合引用关系，从而更好地抵御变化

## 模式定义
用一个中介对象来封装（封装变化）一系列的对象交互。中介者使各对象不需要显式的相互引用（编译时依赖 -> 运行时依赖 ），从而使其耦合松散（管理变化），而且可以独立地改变它们之间的交互

## 结构

![在这里插入图片描述](./pics/%E4%B8%AD%E4%BB%8B%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
- 将多个对象间复杂的关联关系解耦，Mediator 模式将多个对象间的控制逻辑进行集中管理，变“多个对象互相关联”为“多个对象和一个中介者关联”，简化了系统的维护，抵御了可能的变化
- 随着控制逻辑的复杂化，Mediator 具体对象的实现可能相当复杂。这时候可以对 Mediator 对象进行分解处理
- Facade 模式是解耦系统间（单向）的对象关联关系；Mediator 模式是解耦系统内各个对象之间（双向）的关联关系
- 要调整多个对象之间的关系时, 就需要用到 Mediator 模式了。 即不让各个对象之间互相通信,而是增加一个仲裁者角色,让他们各自与仲裁者通信。然后,将控制显示的逻辑处理交给仲裁者负责。

## 应用

### 1. 航空交通管制系统

- **场景**：飞机与控制塔之间的通信
- **中介者**：控制塔
- **参与者**：各个飞机
- **解释**：飞机不直接相互通信，而是通过控制塔协调起飞、降落和航线调整

### 2. 聊天室应用

- **场景**：多人聊天系统
- **中介者**：聊天服务器
- **参与者**：各个用户客户端
- **解释**：用户不直接相互发送消息，而是通过服务器中转，服务器处理消息分发、用户加入/离开等逻辑

### 3. GUI组件交互

- **场景**：复杂表单验证
- **中介者**：表单控制器
- **参与者**：各个表单控件(文本框、复选框等)
- **解释**：当某个控件值变更时，通过中介者协调其他控件的状态更新(如启用/禁用相关字段)

### 4. 物联网设备控制

- **场景**：智能家居系统
- **中介者**：中央智能控制器
- **参与者**：各种智能设备(灯光、温控器、窗帘等)
- **解释**：设备之间通过控制器协调，如"离家模式"下统一关闭所有设备

## 代码

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Mediator;


class Colleague {
protected:
    Mediator*    mediator;
    unsigned int id;

public:
    Colleague(Mediator* const m, const unsigned int i)
        : mediator(m), id(i) {}

    virtual ~Colleague() {}

    unsigned int GetID()
    {
        return id;
    }

    virtual void Send(string)    = 0;
    virtual void Receive(string) = 0;
};

class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* const m, const unsigned int i)
        : Colleague(m, i) {}

    ~ConcreteColleague() {}

    void Send(string msg);

    void Receive(string msg)
    {
        cout << "Message '" << msg << "' received by Colleague " << id << endl;
    }
};


class Mediator {
public:
    virtual ~Mediator() {}
    virtual void Add(Colleague* const colleague)                 = 0;
    virtual void Distribute(Colleague* const sender, string msg) = 0;

protected:
    Mediator() {}
};

class ConcreteMediator : public Mediator {
private:
    vector<Colleague*> colleagues;

public:
    ~ConcreteMediator()
    {
        for (unsigned int i = 0; i < colleagues.size(); i++)
        {
            delete colleagues[i];
        }
        colleagues.clear();
    }

    void Add(Colleague* const colleague)
    {
        colleagues.push_back(colleague);
    }

    void Distribute(Colleague* const sender, string msg)
    {
        for (unsigned int i = 0; i < colleagues.size(); i++)
        {
            if (colleagues.at(i)->GetID() != sender->GetID())
            {
                colleagues.at(i)->Receive(msg);
            }
        }
    }
};

void ConcreteColleague::Send(string msg)
{
    cout << "Message '" << msg << "' sent by Colleague " << id << endl;
    mediator->Distribute(this, msg);
}

void TestMediator(void)
{
    Mediator* mediator = new ConcreteMediator();

    Colleague* c1 = new ConcreteColleague(mediator, 1);
    Colleague* c2 = new ConcreteColleague(mediator, 2);
    Colleague* c3 = new ConcreteColleague(mediator, 3);

    mediator->Add(c1);
    mediator->Add(c2);
    mediator->Add(c3);

    c1->Send("Hi!");
    c3->Send("Hello!");

    delete mediator;
}
```
