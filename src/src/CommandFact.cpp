#include <iostream>

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

void TestCommandFact(void)
{
    Wizard*  pWizard          = new Wizard();
    Command* pSavePrincessCmd = new SavePrincessCommand(pWizard);
    Command* pDefeatDragonCmd = new DefeatDragonCommand(pWizard);

    King* pKing = new King();
    pKing->SetCommand(pSavePrincessCmd);
    pKing->SendCommand();

    pKing->SetCommand(pDefeatDragonCmd);
    pKing->SendCommand();

    delete pSavePrincessCmd;
    delete pDefeatDragonCmd;
    delete pWizard;
    delete pKing;
}
