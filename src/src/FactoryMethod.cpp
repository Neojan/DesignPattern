#include <iostream>

using namespace std;

//工厂方法模式：和简单工厂模式中工厂负责生产所有产品相比，工厂方法模式将生成具体产品的任务分发给具体的产品工厂
//也就是定义一个抽象工厂，其定义了产品的生产接口，但不负责具体的产品，将生产任务交给不同的派生类工厂。这样不用通过指定类型来创建对象了。
//不再只由一个工厂类决定哪一个产品类应当被实例化,这个决定权被交给子类去做。
//当有新的产品产生时，只要按照抽象产品角色、抽象工厂角色提供的方法来生成即可（新产品可以用一个新类继承创建即可），那么就可以被客户使用，而不必去修改任何已有的代码。可以看出工厂角色的结构也是符合开闭原则。

//工厂方法模式：
//一个抽象产品类，可以派生出多个具体产品类。
//一个抽象工厂类，可以派生出多个具体工厂类。
//每个具体工厂类只能创建一个具体产品类的实例。

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

class Factory {
private:
    /* data */
public:
    virtual ProductPhone* CreateProduct() = 0;
};

class MiFactory : public Factory {
private:
    /* data */
public:
    ProductPhone* CreateProduct()
    {
        return new MiPhone();
    }
};

class AppleFactory : public Factory {
private:
    /* data */
public:
    ProductPhone* CreateProduct()
    {
        return new IPhone();
    }
};


void TestFactoryMethod(void)
{
    Factory* factoryMi = new MiFactory();
    ProductPhone* productA = factoryMi->CreateProduct();
    cout << productA->GetName() << endl;

    Factory* factoryApple = new AppleFactory();
    ProductPhone* productB = factoryApple->CreateProduct();
    cout << productB->GetName() << endl;

    delete productA;
    delete productB;
    delete factoryMi;
    delete factoryApple;
}