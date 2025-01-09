#include <iostream>
#include <vector>
#include <memory>

using namespace std;

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
