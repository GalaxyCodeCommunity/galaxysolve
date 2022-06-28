// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdio.h>

_Bool isLeap(int year);

int main()
{
    printf("%s\n", isLeap(2016) ? "true" : "false");
    printf("%s\n", isLeap(2017) ? "true" : "false");
}

_Bool isLeap(int year)
{
    return year % 400 == 0 || (((year & 3) == 0) && year % 100 != 0);
}