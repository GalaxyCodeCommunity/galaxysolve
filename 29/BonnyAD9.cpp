// compiled with 'clang++ -g -Wall -std=c++20'

#define _USE_MATH_DEFINES

// std::abs, std::pow, std::sin

#include <iostream>   // std::cout, std::endl
#include <vector>     // std::vector
#include <cmath>      // M_E
#include <functional> // std::function

#define SMALL_VALUE 0.00001 // used for approximations

// bonus 2
double Newton(std::function<double(double)> &f, double init = 0, double o = SMALL_VALUE);
double LazyDerivative(std::function<double(double)> &f, int x, double o = SMALL_VALUE);
// bonus 1
std::vector<double> AllNewton(std::vector<double> coef, double o = SMALL_VALUE);
void HornerRem(std::vector<double> &coef, double x);
// no bonus
double Newton(std::vector<double> doef, double init = 0, double o = SMALL_VALUE);
double HornerDerivative(std::vector<double> coef, double x);
double Horner(std::vector<double> coef, double x);

int main()
{
    std::vector<double> coef{ 1, 2, -5, -1 };

    // no bonus
    std::cout << Newton(coef) << std::endl; // -0.187284

    // bonus 1
    for (auto r : AllNewton(coef))
        std::cout << r << ' '; // -0.187284 1.57577 -3.38849
    std::cout << std::endl;

    // bonus 2
    std::function<double(double)> f = [](double x)
    {
        return x * std::pow(M_E, std::sin(x)) - 2;
    };

    std::cout << Newton(f) << std::endl; // 0.908809
}

// bonus 2
double Newton(std::function<double(double)> &f, double init, double o)
{
    int lim = std::abs(1 / o);
    for (int i = 0; i < lim; ++i)
    {
        auto ni = init - f(init) / LazyDerivative(f, init, o);
        if (std::abs(ni - init) < o)
            return ni;
        init = ni;
    }
    return NAN;
}

double LazyDerivative(std::function<double(double)> &f, int x, double o)
{
    return (f(x + o) - f(x)) / o;
}

// bonus 1
std::vector<double> AllNewton(std::vector<double> coef, double o)
{
    // coef copy
    auto cc = coef;
    std::vector<double> roots;

    while (cc.size() > 1)
    {
        double r = Newton(cc, 0, o);

        // there are no more roots
        if (isnan(r))
            return roots;

        HornerRem(cc, r);
        roots.push_back(r);
    }

    return roots;
}

void HornerRem(std::vector<double> &coef, double x)
{
    for (int i = 1; i < coef.size(); ++i)
        coef[i] += coef[i - 1] * x;
    coef.pop_back();
}

// no bonus
double Newton(std::vector<double> coef, double init, double o)
{
    const int lim = std::abs(1 / o);
    for (int i = 0; i < lim; ++i)
    {
        double ni = init - Horner(coef, init) / HornerDerivative(coef, init);
        if (std::abs(ni - init) < o)
            return ni;
        init = ni;
    }
    return NAN;
}

double HornerDerivative(std::vector<double> coef, double x)
{
    double res = 0;
    for (size_t i = 0; i < coef.size() - 1; ++i)
        res = res * x + coef[i] * (coef.size() - i - 1);
    return res;
}

double Horner(std::vector<double> coef, double x)
{
    double res = 0;
    for (size_t i = 0; i < coef.size(); ++i)
        res = res * x + coef[i];
    return res;
}
