## 动机
* 在软件构建过程中，集合对象内部结构常常变化各异。但对于这些集合对象，我们希望在不暴露其内部结构的同时，可以让外部客户代码透明地访问其包含的元素；同时这种“透明遍历”也为“同一种算法在多种集合对象上进行操作”提供了可能
* 使用面向对象技术将这种遍历机制抽象为“迭代器对象”为“应对变化中的集合对象”提供了一种优雅的方式

## 模式定义
提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露（稳定）该对象的内部表示

## 结构

![在这里插入图片描述](./pics/%E8%BF%AD%E4%BB%A3%E5%99%A8%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
* 迭代抽象：访问一个聚合对象的内容而无需暴露它的内部表示
* 迭代多态：为遍历不同的集合结构提供一个统一的接口，从而支持同样的算法在不同的集合结构上进行操作
* 迭代器的健壮性考虑：遍历的同时更改迭代器所在的集合结构。会导致问题

## 代码

```cpp
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
```