#include <iostream>
#include <vector>

using namespace std;

class Memento {
private:
    int m_state;

public:
    Memento(const int state) : m_state(state) {}
    int GetState() const
    {
        return m_state;
    }
    void SetState(const int state)
    {
        m_state = state;
    }
};

class Originator {
private:
    int m_state;

public:
    Memento* CreateMemento()
    {
        return new Memento(m_state);
    }
    void SetMemento(Memento* m)
    {
        m_state = m->GetState();
    }
    void SetState(const int state)
    {
        m_state = state;
    }

    int GetState() const
    {
        return m_state;
    }
};

class Caretaker {
private:
    vector<Memento*> m_memento;
    Originator*      m_originator;

public:
    Caretaker(Originator* const pOriginator)
        : m_originator(pOriginator)
    {
    }
    ~Caretaker()
    {
        for (unsigned int i = 0; i < m_memento.size(); i++)
        {
            delete m_memento.at(i);
        }
        
        m_memento.clear();
    }
    void Save()
    {
        cout << "Save state" << endl;
        m_memento.push_back(m_originator->CreateMemento());
    }
    void Undo()
    {
        cout << "Undo state" << endl;
        if (m_memento.empty())
        {
            cout << "Unable to undo state" << endl;
            return;
        }

        Memento* m = m_memento.back();
        m_originator->SetMemento(m);

        m_memento.pop_back();
        delete m;
    }
};


void TestMemento(void)
{
    Originator* pOriginator = new Originator();
    Caretaker*  pCaretaker  = new Caretaker(pOriginator);

    pOriginator->SetState(1);
    pCaretaker->Save();
    pOriginator->SetState(2);
    pCaretaker->Save();
    pOriginator->SetState(3);
    pCaretaker->Save();

    pCaretaker->Undo();
    cout << "Now state is " << pOriginator->GetState() << endl; //output 3
    
    pCaretaker->Undo();
    cout << "Now state is " << pOriginator->GetState() << endl; //output 2
    
    pCaretaker->Undo();
    cout << "Now state is " << pOriginator->GetState() << endl; //output 1

    pCaretaker->Undo();                                         // Unable to undo state
    cout << "Now state is " << pOriginator->GetState() << endl; //output 1

    delete pOriginator;
    delete pCaretaker;
}