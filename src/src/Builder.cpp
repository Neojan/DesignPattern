#include <iostream>

using namespace std;

class House {
private:
    string m_wall;
    string m_door;
    string m_window;

public:
    virtual ~House() {}
    void MakeWall(const string& wall)
    {
        m_wall = wall;
    }
    void MakeDoor(const string& door)
    {
        m_door = door;
    }
    void MakeWindow(const string& window)
    {
        m_window = window;
    }
    void PrintHouse()
    {
        cout << "Wall:" << m_wall << ", Door:" << m_door
             << ", Window:" << m_window << endl;
    }
};

class Builder {
private:
    House m_house;

public:
    virtual ~Builder() {}
    void BuildWall()
    {
        m_house.MakeWall("Normal wall");
    }
    void BuildDoor()
    {
        m_house.MakeDoor("Normal door");
    }
    void BuildWindow()
    {
        m_house.MakeWindow("Normal window");
    }
    House GetHouse()
    {
        return m_house;
    }
};

// class StoneHouse : public House {
// private:
// public:
//     // ...
//     ~StoneHouse() {}
// };
// class StoneHouseBuilder ...

class Director {
private:
    Builder* m_builder;

public:
    Director(Builder* builder)
        : m_builder(builder)
    {
    }
    virtual ~Director()
    {
        if (m_builder)
        {
            delete m_builder;
        }
    }
    void Construct()
    {
        m_builder->BuildWall();
        m_builder->BuildWindow();
        m_builder->BuildDoor();
    }
    House GetHouse() const
    {
        return m_builder->GetHouse();
    }
};


void TestBuilder(void)
{
    Director director(new Builder());
    director.Construct();
    House myHouse = director.GetHouse();
    myHouse.PrintHouse();
}