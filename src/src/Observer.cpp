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