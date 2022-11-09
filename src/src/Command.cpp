#include <iostream>

using namespace std;

class Receiver {
public:
    void Action()
    {
        cout << "Receiver action" << endl;
    }
};

class Command {
public:
    virtual void Execute() = 0;
    virtual ~Command() {}
};

class ConcreteCommand : public Command {
private:
    Receiver* m_recv;

public:
    ConcreteCommand(Receiver* recv)
        : m_recv(recv)
    {
    }
    ~ConcreteCommand() {}
    void Execute()
    {
        m_recv->Action();
    }
};

class Invoker {
private:
    Command* m_command;

public:
    void Set(Command* command)
    {
        m_command = command;
    }
    void Confirm()
    {
        if(m_command)
        {
            m_command->Execute();
        }
    }
};

void TestCommand(void)
{
    Receiver* recv = new Receiver();
    Command*  cmd  = new ConcreteCommand(recv);
    Invoker   invoker;
    invoker.Set(cmd);
    invoker.Confirm();
    delete recv;
    delete cmd;
}