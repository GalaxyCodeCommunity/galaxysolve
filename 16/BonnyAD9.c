// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <math.h>

int digitCount(const int num);

int main()
{
    printf("%d", digitCount(37));
}

int digitCount(const int num)
{
    return num ? (int)log10(abs(num)) + 1 : 1;
}
