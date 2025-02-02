## 动机
- 在软件构建过程中，某些对象的状态在转换过程中，可能由于某种需要，要求程序能够回溯到对象之前处于某个点时的状态。如果使用一些公有接口来让其他对象得到对象的状态，便会暴露对象的细节实现
- 如何实现对象状态的良好保存与恢复，但同时又不会因此而破坏对象本身的封装性？

## 模式定义
在不破环封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原先保存的状态

## 结构

![在这里插入图片描述](./pics/%E5%A4%87%E5%BF%98%E5%BD%95%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
- 备忘录 （Memento）存储原发器（Originator）对象的内部状态，在需要时恢复原发器状态
- Memento 模式的核心是信息隐藏，即 Originator 需要向外界隐藏信息，保持其封装性；但同时又需要将状态保持到外界（Memento）
- 由于现代语言（如C#、Java）运行时都具有相当的序列化支持，因此往往财通效率较高、又较容易正确实现的序列化方案来实现 Memento 模式

## 代码

```cpp
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
```