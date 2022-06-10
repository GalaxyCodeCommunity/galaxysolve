// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

_Bool readColor(FILE* const in);
_Bool isHex(const char c);

int main()
{
    printf("color: ");
    printf("%s", readColor(stdin) ? "true" : "false");
}

_Bool readColor(FILE* const in)
{
    const int len = 9;
    char str[len];

    if (!fgets(str, len, in) || str[0] != '#' || str[len - 2] != '\n')
        return 0;

    for (int i = 1; i < len - 2; i++)
    {
        if (!isHex(str[i]))
            return 0;
    }

    return 1;
}

_Bool isHex(const char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}