#include <iostream>
#include <string>

using namespace std;

// 五种关系的耦合强弱比较：依赖<关联<聚合<组合<继承
// 关联关系的细化：聚合、组合

// 聚合关系，用空心菱形加箭头表示
// 组合关系，用实心菱形加箭头表示，类之间的耦合关系比聚合强！
// 可描述为：Has a
// 在生成代码的时候，关联关系的类会增加属性。

// 不同1：构造函数不同
// 聚合类的构造函数中包含了另一个类作为参数。 雁群类（GooseGroup）的构 造函数中要用到大雁（Goose）作为参数传递进来。大雁类（Goose）可以脱离雁群类而独立存在。
// 组合类的构造函数中包含了另一个类的实例化。 表明大雁类在实例化之前，一定要先实例化翅膀类（Wings），这两个类紧密的耦合在一起，同生共灭。翅膀类（Wings）是不可以脱离大雁类（Goose）而独立存在。

// 不同2：信息的封装性不同
// 在聚合关系中，客户端可以同时了解雁群类和大雁类，因为他们都是独立的。
// 在组合关系中，客户端只认识大雁类，根本就不知道翅膀类的存在，因为翅膀类被严密的封装在大雁类中。

// 聚合：GooseGroup聚合了Goose， 空心菱形指向GooseGroup，箭头指向Goose
// 组合：Goose组合了Wing， 实心菱形指向Goose，箭头指向Wing

class Wing {
public:
    Wing(){};
    ~Wing(){};
};

class Goose {
private:
    Wing* m_Wing;

public:
    Goose()
    {
        m_Wing = new Wing;
    }
    ~Goose()
    {
        delete m_Wing;
    }
};

class GooseGroup {
private:
    Goose m_Goose;

public:
    GooseGroup(Goose goose)
    {
        m_Goose = goose;
    }
    ~GooseGroup() {}
};
