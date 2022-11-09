#include <iostream>

using namespace std;

class Iterator;
class ConcreteAggregate;


class Aggregate {
public:
    virtual ~Aggregate() {}
    virtual Iterator* CreateIterator() = 0;
};

class ConcreteAggregate {
private:
    int* list;
    int  m_size;

public:
    ConcreteAggregate(const unsigned int size)
    {
        list   = new int[size]();
        m_size = size;
    }
    ~ConcreteAggregate()
    {
        delete[] list;
    }
    Iterator*    CreateIterator();
    unsigned int size() const
    {
        return m_size;
    }
    int at(const unsigned int index)
    {
        if (index >= m_size)
        {
            cout << "error index" << endl;
            return -1;
        }
        return list[index];
    }
};


class Iterator {
private:
public:
    virtual ~Iterator() {}
    virtual void First()             = 0;
    virtual void Next()              = 0;
    virtual bool IsDone() const      = 0;
    virtual int  CurrentItem() const = 0;
};

class ConcreteIterator : public Iterator {
private:
    ConcreteAggregate* list;
    unsigned int       index;

public:
    ConcreteIterator(ConcreteAggregate* l)
        : list(l), index(0) {}
    ~ConcreteIterator() {}
    void First()
    {
        index = 0;
    }
    void Next()
    {
        index++;
    }
    bool IsDone() const
    {
        return (index >= list->size());
    }
    int CurrentItem() const {
        return list->at(index);
    }
};

Iterator* ConcreteAggregate::CreateIterator()
{
    return new ConcreteIterator(this);
}

void TestIterator(void)
{
    ConcreteAggregate a(5);
    Iterator*         it = a.CreateIterator();
    for (; !it->IsDone(); it->Next())
    {
        cout << it->CurrentItem() << endl;
    }
    delete it;
}