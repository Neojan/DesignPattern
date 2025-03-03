## 动机
- 在软件系统中，经常有这样一些特殊的类，必须保证它们在系统中只存在一个实例，才能确保它们的逻辑正确性、 以及良好的效率。
- 如何绕过常规的构造器，提供一种机制来保证一个类只有一个实例？
- 这应该是类设计者的责任，而不是使用者的责任。

## 模式定义
- 保证一个类仅有一个实例，并提供一个该实例的全局访问点。

## 结构
![在这里插入图片描述](./pics/%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F.jpeg)

## 要点
- Singleton模式中的实例构造器可以设置为protected以允许子类派生
- Singleton模式一般不要支持拷贝构造函数和clone接口，因为这有可能导致多个对象实例，与Singleton模式的初衷违背
- 如何实现多线程环境下安全的Singleton? 注意对双检查锁的正确实现。
- 例子：全局配置管理、数据库连接池。`ConfigManager.getInstance()`确保全局唯一配置访问入口


## 代码

```cpp
#include <iostream>
#include <mutex>

using namespace std;

class Singleton {
private:
    static Singleton* m_instance;
    static mutex      m_mutex;

    Singleton()
    {
        cout << "new Singleton" << endl;
    }
    Singleton(const Singleton&);
    Singleton&
    operator=(const Singleton&);

public:
    // Singleton(Singleton const &) = delete;
    // Singleton &operator=(const Singleton &) = delete;
    static Singleton* GetInstance()
    {
        if (NULL == m_instance)
        {
            lock_guard<mutex> lock(m_mutex);
            if (NULL == m_instance)
            {
                m_instance = new Singleton();
            }
        }
        return m_instance;
    }
    void Tell()
    {
        cout << "This is Singleton." << endl;
    }
    ~Singleton();
};

Singleton* Singleton::m_instance = nullptr;
mutex      Singleton::m_mutex;

void TestSingleton()
{
    Singleton::GetInstance()->Tell();
    // Singleton a(*Singleton::GetInstance()); //error: ‘Singleton::Singleton(const Singleton&)’ is private within this context
    // Singleton a;                             //error: ‘Singleton::Singleton()’ is private within this context
    // Singleton a = *Singleton::GetInstance(); //error: ‘Singleton::Singleton(const Singleton&)’ is private within this context
}
```
或者
```cpp
class Singleton
{
private:
   Singleton() {} // 私有构造函数
   Singleton(const Singleton&) = delete; // 禁止拷贝
   Singleton& operator=(const Singleton&) = delete; // 禁止赋值

public:
    static Singleton& GetInstance()
    {
        static Singleton instance;
        return instance;
    }
    void Tell()
    {
        std::cout << "This is Singleton." << std::endl;
    }
};
```
