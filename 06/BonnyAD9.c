// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

void swapStrCase(char* restrict str);
char swapCharCase(const int c);

int main()
{
    char str[] = { "aHOJ37" };

    printf("%s\n", str);
    swapStrCase(str);
    printf("%s\n", str);
}

void swapStrCase(char* restrict str)
{
    for (; *str; str++)
        *str = swapCharCase(*str);
}

char swapCharCase(const int c)
{
    const int dif = 'a' - 'A';

    if (c >= 'a' && c <= 'z')
        return c - dif;
    if (c >= 'A' && c <= 'Z')
        return c + dif;

    return c;
}