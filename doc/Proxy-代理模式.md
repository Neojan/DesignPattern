## 动机
- 在面向对象系统中，有些对象由于某种原因（比如对象创建的开销很大，或者某些操作需要安全控制，或者需要进程外的访问等），直接访问会给使用者、或者系统结构带来很多麻烦
- 如何在不失透明操作（一致性）对象的同时来管理/控制这些对象特有的复杂性？增加一层间接层是软件开发中常见的解决方式

## 模式定义
为其他对象提供一种代理以控制（隔离 ，即使用接口）对这个对象的访问

## 结构

![在这里插入图片描述](./pics/%E4%BB%A3%E7%90%86%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
- “增加一层间接层” 是软件系统中对许多复杂问题的一种常见解决方法。在面向对象系统中，直接使用某些对象会带来很多问题，作为间接层的 proxy 对象便是解决这一问题的常用手段
- 具体 proxy 模式的实现方法、实现粒度都相差很大，有些可能对单个对象做细粒度的控制，如 copy-on-write 技术，有些可能对组件模块提供抽象代理层，在架构层次对对象做 proxy
- Proxy 模式并不要求保持接口完整的一致性，只要能够实现间接控制，有时候损失一些透明性是可以接受的
- 示例： 延迟加载优化性能； 访问控制增加安全性；缓存提高响应速度；远程代理隐藏网络细节；智能引用管理资源

## 代码

```cpp
#include <iostream>

using namespace std;

class ISubject {
public:
    virtual ~ISubject(){}
    virtual void Request() = 0;
};

class RawSubject : public ISubject {
public:
    ~RawSubject() {}
    void Request()
    {
        cout << "RawSubject operation" << endl;
    }
};

class Proxy : public ISubject {
private:
    RawSubject* m_rawSubject;

public:
    Proxy()
    {
        //组合了RawSubject
        m_rawSubject = new RawSubject();
    }
    ~Proxy()
    {
        delete m_rawSubject;
    }
    void Request()
    {
        m_rawSubject->Request();
    }
};

void
TestProxy(void)
{
    Proxy* proxy = new Proxy();
    proxy->Request();
    delete proxy;
}
```
