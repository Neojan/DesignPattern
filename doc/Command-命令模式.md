## 动机
- 在软件构建过中，“行为请求者”与“行为实现者”通常呈现一种“紧耦合”。但在某些场合 — 比如需要对行为进行“记录、撤销/重做、事务”等处理，这种无法抵御变化的紧耦合是不合适的
- 在这种情况下，如何将“行为请求者”与“行为实现者”解耦，将一组行为抽象为对象，可以实现二者之间的松耦合

## 模式定义
将一个请求（行为）封装为一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作

## 结构

![在这里插入图片描述](./pics/%E5%91%BD%E4%BB%A4%E6%A8%A1%E5%BC%8F.jpeg)


## 要点
- Command 模式的根本目的在于将“行为请求者”与“行为实现者”解耦，在面向对象语言中，常见的实现手段是“ 将行为抽象为对象 ”
- 实现Command 接口的具体命令对象ConcreteCommand 有时候根据需要可能会保存一些额外的状态信息。通过使用 Composite 模式，可以将多个“命令”封装为一个“ 复合命令 ” MacroCommand

## 实际例子
比如 遥控器（开机 关机）和电视

比如 假设有一个魔法王国，国王统治着整个王国，而魔法师们则拥有各种强大的魔法能力。国王经常需要向魔法师下达各种任务，比如拯救被困的公主、击败恶龙等。在这个故事中，国王是命令发送者，魔法师是命令接收者，而命令模式允许国王将不同的命令封装成对象，并将其发送给魔法师进行执行。


## 代码

```cpp
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
```


```cpp
#include <iostream>
#include <vector>
#include <memory>

class Wizard
{
   public:
    void SavePrincess(void)
    {
        cout << "Wizard is going to save princess..." << endl;
    }

    void DefeatDragon(void)
    {
        cout << "Wizard is going to defeat dragon..." << endl;
    }
};

class Command
{
   public:
    virtual void Execute() = 0;
    virtual ~Command()
    {
    }
};

class SavePrincessCommand : public Command
{
   private:
    Wizard* m_wizard;

   public:
    SavePrincessCommand(Wizard* wizard) : m_wizard(wizard)
    {
    }
    ~SavePrincessCommand()
    {
    }

    void Execute()
    {
        m_wizard->SavePrincess();
    }
};

class DefeatDragonCommand : public Command
{
   private:
    Wizard* m_wizard;

   public:
    DefeatDragonCommand(Wizard* wizard) : m_wizard(wizard)
    {
    }
    ~DefeatDragonCommand()
    {
    }
    void Execute()
    {
        m_wizard->DefeatDragon();
    }
};

class King
{
   private:
    Command* m_cmd;

   public:
    void SetCommand(Command* cmd)
    {
        m_cmd = cmd;
    }
    void SendCommand()
    {
        m_cmd->Execute();
    }
};

// MacroCommand 复合命令对象
class MacroCommand : public Command
{
private:
    std::vector<std::shared_ptr<Command>> commands;

public:
    void addCommand(std::shared_ptr<Command> command)
    {
        commands.push_back(command);
    }

    void removeCommand(size_t index)
    {
        if (index < commands.size())
        {
            commands.erase(commands.begin() + index);
        }
    }

    void Execute() override
    {
        for (auto& command : commands)
        {
            command->Execute();
        }
    }
};

void TestCommandFact(void)
{
    Wizard* pWizard = new Wizard();

    std::shared_ptr<Command> SavePrincessCmd(new SavePrincessCommand(pWizard));
    std::shared_ptr<Command> DefeatDragonCmd(new DefeatDragonCommand(pWizard));
    MacroCommand*            pMacroCommand   = new MacroCommand();
    pMacroCommand->addCommand(SavePrincessCmd);
    pMacroCommand->addCommand(DefeatDragonCmd);

    King* pKing = new King();
    pKing->SetCommand(pMacroCommand);
    // pKing->SetCommand(pSavePrincessCmd);
    // pKing->SetCommand(pDefeatDragonCmd);        
    pKing->SendCommand();

    delete pMacroCommand;
    delete pWizard;
    delete pKing;
}
```
