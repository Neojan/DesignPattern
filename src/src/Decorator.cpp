#include <iostream>

using namespace std;

// 以流为例，流作为基类(相当于图中的Component)，可以派生出网络流，文件流，内存流（相当于图中的ConcreteComponent）;
// 根据是否加密，缓存，又可以派生出加密流，缓存流;
// 如果按照一般的写法，网络流又要派生出加密流，缓存流; 文件流也要派生出加密流，缓存流; 内存流也要派生出加密流，缓存流;
// 子类个数就会成倍的增加
// Decorator提供了一种减少子类的方法, 以此为例，将装饰类继承流基类 ，并聚合流基类，加密流和缓存流继承自装饰类（相当于图中的ConcreteDecorator）

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


class Decorator {
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