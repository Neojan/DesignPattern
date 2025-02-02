## 动机
* 在某些情况下我们可能会“过度地使用继承来扩展对象的功能”，由于继承为类型引入的静态特质，使得这种扩展方式缺乏灵活性；并且随着子类的增多（扩展功能的增多），各种子类的组合（扩展功能的组合）会导致更多子类的膨胀。
* 如何使“对象功能的扩展”能够根据需要来动态地实现？同时避免“扩展功能的增多”带来的子类膨胀问题？从而使得任何“功能扩展变化”所导致的影响将为最低？

## 模式定义
动态（组合）地给一个对象增加一些额外的职责。就增加功能而言，Decorator模式比生成子类（继承）更为灵活（消除重复代码 & 减少子类个数）。——《设计模式》GoF

## 结构

![在这里插入图片描述](./pics/%E8%A3%85%E9%A5%B0%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
* 通过采用组合而非继承的手法， Decorator模式实现了在运行时动态扩展对象功能的能力，而且可以根据需要扩展多个功能。避免了使用继承带来的“灵活性差”和“多子类衍生问题”。
* Decorator类在接口上表现为is-a Component的继承关系，即Decorator类继承了Component类所具有的接口。但在实现上又表现为has-a Component的组合关系，即Decorator类又使用了另外一个Component类。
* Decorator模式的目的并非解决“多子类衍生的多继承”问题，Decorator模式应用的要点在于解决“主体类在多个方向上的扩展功能”——是为“装饰”的含义。
* 例子：1. 动态扩展HTTP客户端功能（如添加缓存、重试）；2. 流

> 如果看到一个类继承自一个父类，同时组合了一个相同父类的成员对象，可以怀疑使用了 Decorator 设计模式

## 代码
// 以流为例，流作为基类(相当于图中的Component)，可以派生出网络流，文件流，内存流（相当于图中的ConcreteComponent）;
// 根据是否加密，缓存，又可以派生出加密流，缓存流;
// 如果按照一般的写法，网络流又要派生出加密流，缓存流; 文件流也要派生出加密流，缓存流; 内存流也要派生出加密流，缓存流;
// 子类个数就会成倍的增加
// Decorator提供了一种减少子类的方法, 以此为例，将装饰类继承流基类 ，并聚合流基类，加密流和缓存流继承自装饰类（相当于图中的ConcreteDecorator）

```cpp
#include <iostream>

using namespace std;

class Stream {
private:
    /* data */
public:
    virtual ~Stream() {}
    virtual void Read(int number)   = 0;
    virtual void Write(char data)   = 0;
    virtual void Seek(int position) = 0;
};

class NetworkStream : public Stream {
private:
    /* data */
public:
    virtual ~NetworkStream() {}
    virtual void Read(int number)
    {
        cout << "Read NetworkStream " << number << endl;
    }
    virtual void Write(char data)
    {
        cout << "Write NetworkStream " << data << endl;
    }
    virtual void Seek(int position)
    {
        cout << "Seek NetworkStream " << position << endl;
    }
};

class FileStream : public Stream {
private:
    /* data */
public:
    virtual ~FileStream() {}
    virtual void Read(int number)
    {
        cout << "Read FileStream " << number << endl;
    }
    virtual void Write(char data)
    {
        cout << "Write FileStream " << data << endl;
    }
    virtual void Seek(int position)
    {
        cout << "Seek FileStream " << position << endl;
    }
};

// class MemoryStream : public Stream ...


class Decorator : public Stream {
private:
    Stream* m_stream;

protected:
    Decorator(Stream* stream)
    {
        m_stream = stream;
    }
    virtual ~Decorator() {}
    virtual void Read(int number)
    {
        m_stream->Read(number);
    }
    virtual void Write(char data)
    {
        m_stream->Write(data);
    }
    virtual void Seek(int position)
    {
        m_stream->Seek(position);
    }
};

class CryptoStream : public Decorator {
private:
    /* data */
public:
    CryptoStream(Stream* stream)
        : Decorator(stream)
    {
    }
    ~CryptoStream() {}
    virtual void Read(int number)
    {
        cout << "Crypto read stream " << number << endl;
        Decorator::Read(number);
    }
    virtual void Write(char data)
    {
        cout << "Crypto write stream " << data << endl;
        Decorator::Write(data);
    }
    virtual void Seek(int position)
    {
        cout << "Crypto seek stream " << position << endl;
        Decorator::Seek(position);
    }
};

// class BufferStream : public Decorator ...

void TestDecorator(void)
{
    CryptoStream a(new FileStream());
    a.Read(10);
    a.Seek(0);
    a.Write(1);
}
```
