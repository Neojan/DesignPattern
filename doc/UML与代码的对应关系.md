
五种关系的耦合强弱比较：依赖<关联<聚合<组合<继承

## 依赖

虚线+箭头

![](https://img-blog.csdn.net/20130505113942124)

可描述为：Uses a

依赖是类的五种关系中耦合最小的一种关系。

因为在生成代码的时候，这两个关系类都不会增加属性。

- 注意1： Water类的生命期，它是当Animal类的GrounUp方法被调用的时候，才被实例化。
- 注意2：持有Water类的是Animal的一个方法而不是Animal类，这点是最重要的！
- 注意3：Water类被Animal类的一个方法持有。生命期随着方法的执行结束而结束 。

```cpp
#include <iostream>
#include <string>

using namespace std;

// 1、表现形式1 :  Water类是全局的，则Animal类可以调用它
// Animal依赖Water
class Water {
private:
public:
    Water() {}
    ~Water() {}
};

class Animal {
private:
public:
    Animal() {}
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
    ~Animal() {}
};
```

## 关联

### 单向关联

实线 + 箭头

![](https://img-blog.csdn.net/20130505114005014)

### 双向关联

![](https://img-blog.csdn.net/20130505114035810)


可描述为：Has a

关联关系用实线，表示类之间的耦合度比依赖强

在生成代码的时候，关联关系的类会增加属性。

- 从类的属性是否增加的角度看
（1）发生依赖关系的两个类都不会增加属性。其中的一个类作为另一个类的方法的参数或者返回值，或者是某个方法的变量而已。
（2）发生关联关系的两个类，其中的一个类成为另一个类的属性，而属性是一种更为紧密的耦合，更为长久的持有关系。

- 从关系的生命期角度看：
 （1）依赖关系是仅当类的方法被调用时而产生，伴随着方法的结束而结束了。
 （2）关联关系是当类实例化的时候即产生，当类销毁的时候，关系结束。相比依赖讲，关联关系的生存期更长。

```cpp
#include <iostream>
#include <string>

using namespace std;

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
```

## 聚合、组合

关联关系的细化：聚合、组合

可描述为：Has a

### 聚合

聚合关系，用空心菱形加箭头表示

![](https://img-blog.csdn.net/20130505114051731)
        

### 组合

组合关系，用实心菱形加箭头表示，类之间的耦合关系比聚合强！

![](https://img-blog.csdn.net/20130505114107012)

在生成代码的时候，关联关系的类会增加属性----即一般为private私有成员变量。

### 聚合和组合的差异

- 构造函数不同

  聚合类的构造函数中包含了另一个类作为参数。 雁群类（GooseGroup）的构 造函数中要用到大雁（Goose）作为参数传递进来。大雁类（Goose）可以脱离雁群类而独立存在。
  
  组合类的构造函数中包含了另一个类的实例化。 表明大雁类在实例化之前，一定要先实例化翅膀类（Wings），这两个类紧密的耦合在一起，同生共灭。翅膀类（Wings）是不可以脱离大雁类（Goose）而独立存在。

- 信息的封装性不同
  
  在聚合关系中，客户端可以同时了解雁群类和大雁类，因为他们都是独立的。
  
  在组合关系中，客户端只认识大雁类，根本就不知道翅膀类的存在，因为翅膀类被严密的封装在大雁类中。

```cpp
#include <iostream>
#include <string>

using namespace std;

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
```

## 继承和实现

可描述为：**Is a**

### 继承

泛化也称继承，子类将继承父类的所有属性和方法，并且可以根据需要对父类进行拓展。

实线+空心箭头

![](https://img-blog.csdn.net/20130505114121433)



> 为什么要多用组合少用继承？
  
  继承和组合各 有优缺点。
  
  类继承是在编译时刻静态定义的，且可直接使用，类继承可以较方便地改变父类的实现。但是类继承也有一些不足之处。首先，因为继承在编译时刻就定义了，所以无法在运行时刻改变从父类继承的实现。更糟的是，父类通常至少定义了子类的部分行为，父类的任何改变都可能影响子类的行为。如果继承下来的实现不适合解决新的问题，则父类必须重写或被其他更适合的类替换。这种依赖关系限制了灵活性并最终限制了复用性。
  
  对象组合是通过获得对其他对象的引用而在运行时刻动态定义的。由于组合要求对象具有良好定义的接口，而且，对象只能通过接口访问，所以我们并不破坏封装性；只要类型一致，运行时刻还可以用一个对象来替代另一个对象；更进一步，因为对象的实现是基于接口写的，所以实现上存在较少的依赖关系。

### 实现

虚线+空心箭头

![](https://img-blog.csdn.net/20130505114134495)


```cpp
#include <iostream>
#include <string>

using namespace std;

// Goose继承自Animal
class Animal {
public:
    Animal() {}
    ~Animal() {}
};

// 实现
// 箭头由Goose指向fly

class Goose : public Animal {
public:
    Goose() {}
    ~Goose() {}
    void fly()
    {
        // interface
    }
};
```
​