// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long filterPrimes(const long* const arr, const size_t length, long* restrict res);
_Bool isPrime(const long num);
void printArr(FILE* out, const long* const arr, const size_t length);

int main()
{
    const size_t len = 4;
    long arr[] = { 1, 3, 50, 10 };

    printArr(stdout, arr, len);
    size_t rlen = filterPrimes(arr, len, arr);
    printArr(stdout, arr, rlen);
}

long filterPrimes(const long* const arr, const size_t length, long* restrict res)
{
    size_t r = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (isPrime(arr[i]))
            res[r++] = arr[i];
    }
    return r;
}

_Bool isPrime(const long num)
{
    if (num == 2 || num == 3)
        return 1;

    if ((num & 1) == 0 || num < 2 || num % 3 == 0)
        return 0;

    int lim = sqrt(num);
    for (long i = 6; i <= lim; i += 6)
    {
        if (num % (i - 1) == 0 || num % (i + 1) == 0)
            return 0;
    }

    return 1;
}

void printArr(FILE* out, const long* const arr, const size_t length)
{
    if (length == 0)
    {
        fprintf_s(out, "[]");
        return;
    }

    fprintf_s(out, "[%ld", *arr);
    for (size_t i = 1; i < length; i++)
        fprintf_s(out, ", %ld", arr[i]);
    fprintf_s(out, "]\n");
}