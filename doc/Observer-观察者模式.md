## 动机
- 在软件构建过程中，我们需要为某些对象建立一种“通知依赖关系” ——一个对象（目标对象）的状态发生改变，所有的依赖对象（观察者对象）都将得到通知。如果这样的依赖关系过于紧密，将使软件不能很好地抵御变化。
- 使用面向对象技术，可以将这种依赖关系弱化，并形成一种稳定的依赖关系。从而实现软件体系结构的松耦合。

## 模式定义
定义对象间的一种一对多（变化）的依赖关系，以便当一个对象(Subject)的状态发生改变时，所有依赖于它的对象都得到通知并自动更新。——《设计模式》 GoF

## 结构

![在这里插入图片描述](./pics/%E8%A7%82%E5%AF%9F%E8%80%85%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
-  使用面向对象的抽象， Observer模式使得我们可以独立地改变目标与观察者，从而使二者之间的依赖关系达致松耦合。
-  目标发送通知时，无需指定观察者，通知（可以携带通知信息作为参数）会自动传播。
-  观察者自己决定是否需要订阅通知，目标对象对此一无所知。
-  Observer模式是基于事件的UI框架中非常常用的设计模式，也是MVC模式的一个重要组成部分。

## 与发布订阅模式区别

两种设计模式思路是一样的，举个生活例子：

- 观察者模式：某公司给自己员工发月饼发粽子，是由公司的行政部门发送的，这件事不适合交给第三方，原因是“公司”和“员工”是一个整体
- 发布-订阅模式：某公司要给其他人发各种快递，因为“公司”和“其他人”是独立的，其唯一的桥梁是“快递”，所以这件事适合交给第三方快递公司解决

上述过程中，如果公司自己去管理快递的配送，那公司就会变成一个快递公司，业务繁杂难以管理，影响公司自身的主营业务，因此使用何种模式需要考虑什么情况两者是需要耦合的

两者区别如下图：

- 在观察者模式中，观察者是知道Subject的，Subject一直保持对观察者进行记录。然而，在发布订阅模式中，发布者和订阅者不知道对方的存在。它们只有通过消息代理进行通信。
    
- 在发布订阅模式中，组件是松散耦合的，正好和观察者模式相反。
    
- 观察者模式大多数时候是同步的，比如当事件触发，Subject就会去调用观察者的方法。而发布-订阅模式大多数时候是异步的（使用消息队列）

## 代码

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Subject;

class Observer {
public:
    virtual void Update(Subject*) = 0;
};

class ConcreteObserver : public Observer {
private:
    int m_observerState;
public:
    ConcreteObserver(const int state)
        : m_observerState(state) {}
    int GetState() const
    {
        return m_observerState;
    }
    void Update(Subject* subject);
};

class Subject {
private:
    vector<Observer*> m_observer;
public:
    virtual ~Subject() {}
    virtual int  GetState() const                 = 0;
    virtual void SetState(const int subjectState) = 0;
    void         Attach(Observer* ob)
    {
        m_observer.push_back(ob);
    }
    void Detach(Observer* ob)
    {
        // or find(algorithm) and erase;
        for (unsigned int i = 0; i < m_observer.size(); i++)
        {
            if (ob == m_observer.at(i))
            {
                cout << "erase " << i << endl;
                m_observer.erase(m_observer.begin() + i);
            }
        }
    }
    void Notify();
};

void Subject::Notify()
{
    for (unsigned int i = 0; i < m_observer.size(); i++)
    {
        m_observer.at(i)->Update(this);
    }
}

class ConcreteSubject : public Subject {
private:
    int m_subjectState;

public:
    ~ConcreteSubject() {}
    int GetState() const
    {
        return m_subjectState;
    }
    void SetState(const int subjectState)
    {
        m_subjectState = subjectState;
    }
};

void ConcreteObserver::Update(Subject* subject)
{
    m_observerState = subject->GetState();
}

void TestObserver(void)
{
    ConcreteObserver observer1(1);
    ConcreteObserver observer2(2);

    std::cout << "Observer 1 state: " << observer1.GetState() << std::endl;
    std::cout << "Observer 2 state: " << observer2.GetState() << std::endl;

    Subject* subject = new ConcreteSubject();
    subject->Attach(&observer1);
    subject->Attach(&observer2);
    subject->SetState(10);
    subject->Notify();

    std::cout << "Observer 1 state: " << observer1.GetState() << std::endl;
    std::cout << "Observer 2 state: " << observer2.GetState() << std::endl;

    subject->Detach(&observer2);
    subject->SetState(20);
    subject->Notify();

    std::cout << "Observer 1 state: " << observer1.GetState() << std::endl;
    std::cout << "Observer 2 state: " << observer2.GetState() << std::endl;

    delete subject;
}
```
