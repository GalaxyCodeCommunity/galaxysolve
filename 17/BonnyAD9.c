// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <ctype.h>

char mostUsedAlpha(const char *str);
size_t max(const int * const arr, const size_t length);

int main()
{
    printf("%c", mostUsedAlpha("parek v rohliku")); // k
}

char mostUsedAlpha(const char *str)
{
    int counts[256] = { 0 };

    do counts[tolower((unsigned char)*str++)]++;
    while (*str);

    return max(counts + 'a', 'z' - 'a') + 'a';
}

size_t max(const int * const arr, const size_t length)
{
    size_t m = 0;

    for (size_t i = 0; i < length; ++i)
    {
        if (arr[i] > arr[m])
            m = i;
    }

    return m;
}
