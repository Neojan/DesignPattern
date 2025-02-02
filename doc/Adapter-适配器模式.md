## 动机
* 在软件系统中，由于应用环境的变化，常常需要将“一些现存的对象”放在新的环境中使用，但是新环境要求的接口是这些现存对象所不满足的
* 如何应对这种“迁移的变化”，如何既能利用现有对象的良好实现，同时又能满足新的应用环境所要求的接口？

## 模式定义
将一个类的接口转成客户希望的另一个接口。Adapter 模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作

## 结构

![在这里插入图片描述](./pics/%E9%80%82%E9%85%8D%E5%99%A8%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
继承新接口，组合旧接口
* Adapter 模式主要应用于“希望复用一些现存的类，但是接口又与复用环境要求不一致的情况”，在遗留代码复用、类库迁移等方面非常有用
* GoF 定义了两种 Adapter 模式的实现结构：对象适配器和类适配器。但类适配器采用“多继承”的实现方式，一般不推荐使用（不够灵活）；对象适配器采用“对象组合”的方式，更符合松耦合精神
* Adapter 模式可以实现的非常灵活，不必拘泥于 Gof 中定义的两种结构。例如，完全可以将Adapter 模式中的“现存对象”作为新的接口方法参数，来达到适配的目的
* 例子：整合第三方支付接口（如支付宝适配银联标准）。`AlipayAdapter`实现`PaymentGateway`接口，内部调用支付宝SDK方法。

## 代码

```cpp
#include <iostream>

using namespace std;

class Target {
public:
    virtual ~Target() {}
    virtual void Request() = 0;
};

class Adaptee {
public:
    ~Adaptee() {}
    void SpecificRequest()
    {
        cout << "SpecificRequest" << endl;
    }
};

//Object Adapter
class Adapter1 : public Target {
private:
    Adaptee* m_adaptee;

public:
    Adapter1()
    {
        m_adaptee = new Adaptee();
    }
    ~Adapter1()
    {
        delete m_adaptee;
    }
    void Request()
    {
        m_adaptee->SpecificRequest();
    }
};

//Class Adapter
class Adapter2 : public Target, private Adaptee {
public:
    virtual void Request()
    {
        SpecificRequest();
    }
    // ...
};


void TestAdapter(void)
{
    Target* t1 = new Adapter1();
    t1->Request();
    delete t1;

    Target* t2 = new Adapter2();
    t2->Request();
    delete t2;
}
```