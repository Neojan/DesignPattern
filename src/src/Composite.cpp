#include <iostream>
#include <vector>

using namespace std;

class Component {
public:
    virtual ~Component() {}
    virtual void Add(Component* const) {}
    virtual void Remove(const int) {}
    virtual void Operation() = 0;
};

class Leaf : public Component {
private:
    int m_id;

public:
    Leaf(const int id)
        : m_id(id) {}
    ~Leaf() {}
    void Operation()
    {
        cout << "Leaf " << m_id << " operation" << endl;
    }
};


class Composite : public Component {
private:
    vector<Component*> m_component;

public:
    ~Composite()
    {
        for (int i = 0; i < m_component.size(); i++)
        {
            delete m_component[i];
        }
    }
    void Add(Component* const c)
    {
        m_component.push_back(c);
    }
    void Remove(const int index)
    {
        if (index >= m_component.size())
        {
            cout << "index over max size " << m_component.size() << endl;
            return;
        }
        Component* child = m_component[index];
        m_component.erase(m_component.begin() + index);
        delete child;
    }
    void Operation()
    {
        for (int i = 0; i < m_component.size(); i++)
        {
            m_component[i]->Operation();
        }
    }
};

void TestComposite(void)
{
    Composite composite;
    composite.Add(new Leaf(1));
    composite.Add(new Leaf(2));
    composite.Add(new Leaf(3));
    composite.Remove(2);
    composite.Operation();
}