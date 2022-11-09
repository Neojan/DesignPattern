#include <iostream>
#include <string>

using namespace std;

// 五种关系的耦合强弱比较：依赖<关联<聚合<组合<继承
// 关联
// 实线 + 箭头 ---->
// 可描述为：Has a
// 关联关系用实线，表示类之间的耦合度比依赖强
// 在生成代码的时候，关联关系的类会增加属性。

// 1、从类的属性是否增加的角度看
//（1）发生依赖关系的两个类都不会增加属性。其中的一个类作为另一个类的方法的参数或者返回值，或者是某个方法的变量而已。
//（2）发生关联关系的两个类，其中的一个类成为另一个类的属性，而属性是一种更为紧密的耦合，更为长久的持有关系。

// 2、从关系的生命期角度看：
//（1）依赖关系是仅当类的方法被调用时而产生，伴随着方法的结束而结束了。
//（2）关联关系是当类实例化的时候即产生，当类销毁的时候，关系结束。相比依赖讲，关联关系的生存期更长。

// Water关联Climate

class Climate;
class Water;

class Water {
private:
    Climate* m_Climate; // Water类的属性中增加了Climate类。
public:
    Water() {}
    ~Water() {}
};

class Climate {
private:
    Water* m_Water; // 双向关联
public:
    Climate() {}
    ~Climate() {}
};
