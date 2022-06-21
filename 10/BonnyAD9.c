// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

size_t zip(const int* const arr1, const size_t len1, const int* const arr2, const size_t len2, int* const restrict out, const size_t outLen);
void printArr(const int* const arr, const size_t length);

int main()
{
    const int len1 = 2;
    const int len2 = 2;
    const int resLen = len1 + len2;

    int arr1[] = { 1, 2 };
    int arr2[] = { 3, 4 };
    int res[resLen];

    int l = zip(arr1, len1, arr2, len2, res, resLen);

    printArr(res, l);
}

size_t zip(const int* const arr1, const size_t len1, const int* const arr2, const size_t len2, int* const restrict out, const size_t outLen)
{
    // zip two arrays
    size_t pos = 0;
    size_t i = 0;
    for (; i < len1 && i < len2 && pos < outLen; i++)
    {
        out[pos++] = arr1[i];
        if (pos >= outLen)
            return pos;
        out[pos++] = arr2[i];
    }

    if (pos >= outLen)
        return pos;

    // if one of the arrays is longer, copy it to the output
    const int* arr = arr2;
    size_t len = len2;
    if (len1 > len2)
    {
        arr = arr1;
        len = len1;
    }

    for (; i < len && pos < outLen; i++, pos++)
        out[pos] = arr[i];

    // return the number of written elements
    return pos;
}

void printArr(const int* const arr, const size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%d ", arr[i]);
}