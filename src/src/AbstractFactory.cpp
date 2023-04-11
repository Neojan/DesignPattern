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
        return new MiPhone();
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