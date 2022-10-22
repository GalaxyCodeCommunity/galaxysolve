// compiled with 'clang++ -g -Wall -std=c++20'

#define _USE_MATH_DEFINES

#include <iostream> // std::cout, std::endl
#include <array> // std::array
#include <cmath> // M_PI

// just trying generics
template<typename Iterator>
auto GetAngle(Iterator s1, Iterator e1, Iterator s2, Iterator e2)
    -> decltype(*s1 * *s1, *s1 + *s1, acos(*s1));

void Rotate(double &x, double &y, double angle);

int main()
{
    std::array<double, 2> vec1{ 4, 2 };
    std::array<double, 2> vec2{ -1, 4 };
    std::cout
        << GetAngle(vec1.begin(), vec1.end(), vec2.begin(), vec2.end())
        << std::endl;

    double x = -1;
    double y = 4;
    Rotate(x, y, M_PI / 2);
    std::cout << x << ' ' << y << std::endl;
}

template<typename Iterator>
auto GetAngle(Iterator s1, Iterator e1, Iterator s2, Iterator e2)
    -> decltype(*s1 * *s1, *s1 + *s1, acos(*s1))
{
    auto dot = 0;
    auto l1 = 0;
    auto l2 = 0;
    for (; s1 != e1 && s2 != e2; ++s1, ++s2)
    {
        dot += *s1 * *s2;
        l1 += *s1 * *s1;
        l2 += *s2 * *s2;
    }
    return acos(abs(dot) / (sqrt(l1) * sqrt(l2)));
}

void Rotate(double &x, double &y, double angle)
{
    double h = cos(angle) * x - sin(angle) * y;
    y = sin(angle) * x + cos(angle) * y;
    x = h;
}
