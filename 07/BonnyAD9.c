// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

int bCount(const char* str);

int main()
{
    char s1[] = "cau (mega (dobre)) (fakt jo)";
    char s2[] = "cau (mega (dobre)) (fakt jo";
    char s3[] = "cau (mega (dobre)) fakt jo)";

    printf("'%s': %d\n", s1, bCount(s1));
    printf("'%s': %d\n", s2, bCount(s2));
    printf("'%s': %d\n", s3, bCount(s2));
}

int bCount(const char* str)
{
    int b = 0, n = 0;
    for (; *str; str++)
    {
        n += *str == '(';
        _Bool a = *str == ')' && n > 0;
        n -= a;
        b += a;
    }
    return b;
}