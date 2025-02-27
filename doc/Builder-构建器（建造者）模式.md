## 动机
- 在软件系统中，有时候面临着“一个复杂对象”的创建工作，其通常由各个部分的子对象用一定的算法构成；由于需求的变化，这个复杂对象的各个部分经常面临着剧烈的变化，但是将它们组合在一起的算法却相对稳定。
- 如何应对这种变化？如何提供一种“封装机制”来隔离出“复杂对象的各个部分”的变化，从而保持系统中的“稳定构建算法”不随着需求改变而改变？

## 模式定义
将一个复杂对象的构建与其表示相分离，使得同样的构建过程(稳定)可以创建不同的表示(变化)

## 结构

![在这里插入图片描述](./pics/%E6%9E%84%E5%BB%BA%E5%99%A8.jpeg)

## 要点
- Builder 模式主要用于“分步骤构建一个复杂的对象”。在这其中“分步骤”是一个稳定的算法，而复杂对象的各个部分则经常变化。
- 变化点在哪里，封装哪里—— Builder模式主要在于应对“复杂对象各个部分”的频繁需求变动。其缺点在于难以应对“分步骤构建算法”的需求变动。
- 在Builder模式中，要注意不同语言中构造器内调用虚函数的差别（C++ vs. C#）。
- 补充：Builder和Product部分与工厂模式基本相似，但Builder多了Director部分
- 例子：构造复杂HTTP请求（需设置URL、Header、Body等参数）。HttpRequest.Builder()链式调用设置URL、Header、Body，最后调用build()生成不可变对象。

## 代码

```cpp
#include <iostream>

using namespace std;

class House {
private:
    string m_wall;
    string m_door;
    string m_window;

public:
    virtual ~House() {}
    void MakeWall(const string& wall)
    {
        m_wall = wall;
    }
    void MakeDoor(const string& door)
    {
        m_door = door;
    }
    void MakeWindow(const string& window)
    {
        m_window = window;
    }
    void PrintHouse()
    {
        cout << "Wall:" << m_wall << ", Door:" << m_door
             << ", Window:" << m_window << endl;
    }
};

class Builder {
private:
    House m_house;

public:
    virtual ~Builder() {}
    void BuildWall()
    {
        m_house.MakeWall("Normal wall");
    }
    void BuildDoor()
    {
        m_house.MakeDoor("Normal door");
    }
    void BuildWindow()
    {
        m_house.MakeWindow("Normal window");
    }
    House GetHouse()
    {
        return m_house;
    }
};

// class StoneHouse : public House {
// private:
// public:
//     // ...
//     ~StoneHouse() {}
// };
// class StoneHouseBuilder ...

class Director {
private:
    Builder* m_builder;

public:
    Director(Builder* builder)
        : m_builder(builder)
    {
    }
    virtual ~Director()
    {
        if (m_builder)
        {
            delete m_builder;
        }
    }
    void Construct()
    {
        m_builder->BuildWall();
        m_builder->BuildWindow();
        m_builder->BuildDoor();
    }
    House GetHouse() const
    {
        return m_builder->GetHouse();
    }
};


void TestBuilder(void)
{
    Director director(new Builder());
    director.Construct();
    House myHouse = director.GetHouse();
    myHouse.PrintHouse();
}
```