## 动机
* 软件在某些情况下，客户代码过多地依赖于对象容器复杂的内部实现结构，对象容器内部实现结构（而非抽象接口）的变化将引起客户代码的频繁变化，为代码的维护性、扩展性等带来了弊端
* 如何将“客户代码与复杂的对象容器结构”解耦，让对象容器自己来实现自身的复杂结构，从而使得客户代码就像处理简单对象一样来处理复杂的对象容器？

## 模式定义
将对象组合成树形结构以表示“部分-整体”的层次结构。Composite 使得用户对单个对象和组合对象的使用具有一致性（稳定）

## 结构

![在这里插入图片描述](./pics/%E7%BB%84%E5%90%88%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
* Composite 模式采用树形结构来实现普遍存在的对象容器，从而将“ 一对多 ”的关系转换为“ 一对一 ”的关系，使得客户代码可以一致地（复用）处理对象和对象容器，无需关心处理的是单个对象还是组合的对象容器
* 将“客户代码与复杂的对象容器结构”解耦是 Composite 模式的核心思想，解耦之后，客户代码将与纯粹的抽象接口 — 而非对象容器的内部实现结构 — 发生依赖，从而更能“应对变化”
* Composite 模式在具体实现中，可以让父对象中的子对象反向追溯；如果父对象有频繁的遍历需求，可使用缓存技巧来改善效率

## 代码

```cpp
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
```