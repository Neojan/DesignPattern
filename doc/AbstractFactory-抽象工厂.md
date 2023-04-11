## 动机
* 在软件系统中，经常面临着“一系列相互依赖的对象”的创建工作；同时，由于需求的变化，往往存在更多系列对象的创建工作。
* 如何应对这种变化？如何绕过常规的对象创建方法(new)，提供一种“封装机制”来避免客户程序和这种“多系列具体对象创建工作”的紧耦合

## 模式定义
提供一个接口，让该接口负责创建一系列“相关或者相互依赖的对象”，无需指定它们具体的类

## 结构

![在这里插入图片描述](./pics/%E6%8A%BD%E8%B1%A1%E5%B7%A5%E5%8E%82.jpeg)

## 要点
* 如果没有应对“多系列对象构建”的需求变化，则没有必要使用Abstract Factory模式，这时候使用简单的工厂完全可以。
* “系列对象”指的是在某一特定系列下的对象之间有相互依赖、或作用的关系。不同系列的对象之间不能相互依赖。
* Abstract Factory模式主要在于应对“新系列”的需求变动。其缺点在于难以应对“新对象”的需求变动

## 代码

```cpp
#include <iostream>

using namespace std;

// 抽象工厂：将工厂和产品都抽象出来
// 比如定义一个抽象工厂，工厂可以生产手机和电脑
// 小米工厂继承自抽象工厂，小米工厂可以生产出小米手机和小米电脑
// 苹果工厂继承自抽象工厂，苹果工厂可以生产出苹果手机和苹果电脑


class ProductPhone {
private:
    /* data */
public:
    virtual ~ProductPhone() {}
    virtual string GetName() = 0;
};

class IPhone : public ProductPhone {
private:
    /* data */
public:
    IPhone()
    {
        cout << "iPhone create" << endl;
    }
    ~IPhone() {}
    string GetName()
    {
        return "iPhone";
    }
};

class MiPhone : public ProductPhone {
private:
    /* data */
public:
    MiPhone()
    {
        cout << "MiPhone create" << endl;
    }
    ~MiPhone() {}
    string GetName()
    {
        return "MiPhone";
    }
};

class ProductPC {
private:
    /* data */
public:
    virtual ~ProductPC() {}
    virtual string GetName() = 0;
};

class MiBook : public ProductPC {
private:
    /* data */
public:
    MiBook()
    {
        cout << "MiBook create" << endl;
    }
    ~MiBook() {}
    string GetName()
    {
        return "MiBook";
    }
};

class AppleMacBook : public ProductPC {
private:
    /* data */
public:
    AppleMacBook()
    {
        cout << "AppleMacBook create" << endl;
    }
    ~AppleMacBook() {}
    string GetName()
    {
        return "Apple MacBook";
    }
};

class AbstractFactory {
private:
    /* data */
public:
    virtual ~AbstractFactory() {}
    virtual ProductPhone* CreatePhone() = 0;
    virtual ProductPC*    CreatePC()    = 0;
};

class MiFactory : public AbstractFactory {
private:
    /* data */
public:
    ProductPhone* CreatePhone()
    {
        return new IPhone();
    }
    ProductPC* CreatePC()
    {
        return new MiBook();
    }
};

class AppleFactory : public AbstractFactory {
private:
    /* data */
public:
    ProductPhone* CreatePhone()
    {
        return new IPhone();
    }
    ProductPC* CreatePC()
    {
        return new AppleMacBook();
    }
};


void TestAbstractFactory(void)
{
    //每个工厂负责生产一种产品
    AbstractFactory* factoryMi = new MiFactory();
    ProductPhone*    miPhone   = factoryMi->CreatePhone();
    ProductPC*       miBook    = factoryMi->CreatePC();
    cout << miPhone->GetName() << endl;
    cout << miBook->GetName() << endl;

    AbstractFactory* factoryApple = new AppleFactory();
    ProductPhone*    iPhone       = factoryApple->CreatePhone();
    ProductPC*       macBook      = factoryApple->CreatePC();
    cout << iPhone->GetName() << endl;
    cout << macBook->GetName() << endl;

    delete miPhone;
    delete miBook;
    delete iPhone;
    delete macBook;
    delete factoryMi;
    delete factoryApple;
}
```