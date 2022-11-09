#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class String {
public:
    String(const char* data = 0)
    {
        if (data)
        {
            m_data = new char[strlen(data) + 1];
            strcpy(m_data, data);
        }
        else
        {
            m_data    = new char[1];
            m_data[0] = '\0';
        }
    }
    String(const String& str)
    {
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
    }
    String& operator=(const String& str)
    {
        if (&str == this)
        {
            return *this;
        }

        delete[] m_data;

        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);

        return *this;
    }
    const char* get_c_str() const
    {
        return m_data;
    }
    ~String()
    {
        delete[] m_data;
    }

private:
    char* m_data;
};

void testString(void)
{
    String testStr("12345");
    cout << testStr.get_c_str() << endl;
}
