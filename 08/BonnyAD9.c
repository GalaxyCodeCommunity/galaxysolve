// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

double fmap(const double x, const double a, const double b, const double c, const double d);

int main()
{
    printf("5:   0..10  == %lf: 0..100\n", fmap(5, 0, 10, 0, 100));
    printf("65: 50..100 == %lf: 0..255\n", fmap(65, 50, 100, 0, 255));
}

double fmap(const double x, const double a, const double b, const double c, const double d)
{
    return (x - a) * (d - c) / (b - a) + c;
}