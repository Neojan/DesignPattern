#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Complex {
private:
    double m_real;
    double m_img;

public:
    Complex(double real = 0, double img = 0)
        : m_real(real), m_img(img)
    {
    }
    double GetReal() const
    {
        return m_real;
    }
    double GetImg() const
    {
        return m_img;
    }
    Complex&        operator+=(const Complex&);
    friend Complex& _doapl(Complex*, const Complex&);
};

Complex& _doapl(Complex* ths, const Complex& r)
{
    ths->m_real += r.m_real;
    ths->m_img += r.m_img;
    return *ths;
}

Complex& Complex::operator+=(const Complex& input)
{
    return _doapl(this, input);
}

int testComplex(void)
{
    Complex  test(1);
    Complex  test2(1, -1);
    Complex* test3 = new Complex;
    test += test2;
    cout << test.GetReal() << ',' << test.GetImg() << endl;
    getchar();

    return 0;
}