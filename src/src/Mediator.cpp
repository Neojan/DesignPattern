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