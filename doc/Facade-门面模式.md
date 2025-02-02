![在这里插入图片描述](./pics/%E9%97%A8%E9%9D%A2%E6%A8%A1%E5%BC%8F2.jpeg)

## 动机
- 上述A方案的问题在于组件的客户和组件中各种复杂的子系统有过多的耦合，随着外部客户程序和各子系统的演化，这种过多的耦合会面临很多变化的挑战
- 如何简化外部客户程序和系统间的交互接口，如何将外部客户程序的演化和内部子系统的变化之间的依赖相互解耦？

## 模式定义
- 为子系统中的一组接口提供一个一致（稳定）的界面，Facade 模式定义了一个高层接口，这个接口使得这一子系统更加容易使用（复用）（隔离变化和稳定）结构

## 结构

![在这里插入图片描述](./pics/%E9%97%A8%E9%9D%A2%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
- 从客户程序角度来看，Facade 模式简化了整个组件系统的接口，对于组件内部与外部客户程序来说，达到了一种“ 解耦 ”的效果 — 内部子系统的任何变化不会影响到Facade 接口的变化
- Facade 模式更注重从架构 的层次去看整个系统，而不是单个类的层次。Facade 很多时候更像是一种架构设计模式
- Facade 模式并非一个集装箱，可以任意地放进任何多个对象，Facade 模式中组件的内部应该是“ 相互耦合关系比较大的一系列组件 ”，而不是一个简单的功能集合
- 例子：简化复杂子系统调用（如订单系统一键下单）。OrderFacade封装库存校验、支付、物流通知等步骤，对外暴露placeOrder()方法。
- 例子：比如快捷指令或者场景，起床场景（配合闹钟，打开窗帘，播放音乐等）

## 代码

```cpp
#include <iostream>

using namespace std;

class SubsystemA {
public:
    void suboperation()
    {
        std::cout << "Subsystem A method" << std::endl;
        // ...
    }
    // ...
};

class SubsystemB {
public:
    void suboperation()
    {
        std::cout << "Subsystem B method" << std::endl;
        // ...
    }
    // ...
};

class SubsystemC {
public:
    void suboperation()
    {
        std::cout << "Subsystem C method" << std::endl;
        // ...
    }
    // ...
};

class Facade {
private:
    SubsystemA* subsystemA;
    SubsystemB* subsystemB;
    SubsystemC* subsystemC;
    // ...
public:
    Facade()
    {
        subsystemA = new SubsystemA();
        subsystemB = new SubsystemB();
        subsystemC = new SubsystemC();
    }
    ~Facade()
    {
        delete subsystemA;
        delete subsystemB;
        delete subsystemC;
    }

    void operation1()
    {
        subsystemA->suboperation();
        subsystemB->suboperation();
        // ...
    }

    void operation2()
    {
        subsystemC->suboperation();
        // ...
    }
    // ...
};


void TestFacade(void)
{
    Facade* facade = new Facade();
    facade->operation1();
    facade->operation2();
    delete facade;
}
```