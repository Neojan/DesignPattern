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
        // static Singleton m_instance;
        // return m_instance;
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