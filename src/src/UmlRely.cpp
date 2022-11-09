#include <iostream>
#include <string>

using namespace std;

// 五种关系的耦合强弱比较：依赖<关联<聚合<组合<继承
// 依赖
// 虚线+箭头 ---->
// 可描述为：Use a
// 依赖是类的五种关系中耦合最小的一种关系。
// 因为在生成代码的时候，这两个关系类都不会增加属性。

// 注意1： Water类的生命期，它是当Animal类的GrounUp方法被调用的时候，才被实例化。
// 注意2：持有Water类的是Animal的一个方法而不是Animal类，这点是最重要的！
// 注意3：Water类被Animal类的一个方法持有。生命期随着方法的执行结束而结束 。

// 1、表现形式1 :  Water类是全局的，则Animal类可以调用它
// Animal依赖Water
class Water {
public:
    Water() {}
    ~Water() {}
};

class Animal {
public:
    Animal() {}
    ~Animal() {}
    // 2、表现形式2:   Water类是 Animal类的某个方法中的变量，则Animal类可以调用它。
    void GrownUp()
    {
        Water useWater;
    }
    // 3、表现形式3: Water类是作为Animal类中某个方法的参数或者返回值
    Water GrownUp2(Water useWater)
    {
        return useWater;
    }
};
