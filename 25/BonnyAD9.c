// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

int **allPermutations(int *arr, size_t len, size_t *rlen);
size_t factorial(size_t n);
int intcmp(const void *a, const void *b);
_Bool nextPerm(int *arr, size_t len);
void reverse(int *arr, size_t len);
void swap(int *a, int *b);
void printArr(int *arr, size_t len);
void printArr2(int **arr, size_t len1, size_t len2);
void rfree(void **val, size_t len);

int main()
{
    int arr[] = { 1, 2, 3 };
    const size_t len = sizeof(arr) / sizeof(int);

    size_t plen;
    int **p = allPermutations(arr, len, &plen);
    if (!p)
    {
        printf("Error\n");
        return EXIT_FAILURE;
    }

    printArr2(p, plen, len);
}

int **allPermutations(int *arr, size_t len, size_t *rlen)
{
    int count = factorial(len);
    int *buffer = malloc(sizeof(int) * len);
    if (!buffer)
        return NULL;

    memcpy(buffer, arr, len * sizeof(int));
    qsort(buffer, len, sizeof(int), intcmp);

    int c = 1;
    for (int i = 1; i < len; ++i, ++c)
    {
        if (arr[i] == arr[i - 1])
            continue;

        count /= factorial(c);
        c = 0;
    }

    int **res = malloc(sizeof(int *) * count);
    if (!res)
    {
        free(buffer);
        return NULL;
    }

    *res = buffer;
    for (int i = 1; i < count; ++i)
    {
        int *b2 = malloc(sizeof(int) * len);
        if (!b2)
        {
            rfree((void **)res, i);
            return NULL;
        }
        memcpy(b2, buffer, len * sizeof(int));
        buffer = b2;
        nextPerm(buffer, len);
        res[i] = buffer;
    }

    if (rlen)
        *rlen = count;
    return res;
}

size_t factorial(size_t n)
{
    size_t r = 1;
    for (; n > 1; --n)
        r *= n;
    return r;
}

int intcmp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

_Bool nextPerm(int *arr, size_t len)
{
    if (len <= 1)
        return 0;

    size_t p = len - 2;
    for (; p != SIZE_MAX && arr[p] > arr[p + 1]; --p)
        ;

    if (p == SIZE_MAX)
        return 0;

    size_t ps = arr[len - 1];
    for (; arr[ps] <= arr[p]; --ps)
        ;

    swap(arr + p, arr + ps);
    reverse(arr + p + 1, len - p - 1);

    return 1;
}

void reverse(int *arr, size_t len)
{
    for (; len > 1; len -= 2, ++arr)
        swap(arr, arr + len - 1);
}

void swap(int *a, int *b)
{
    int h = *a;
    *a = *b;
    *b = h;
}

void printArr(int *arr, size_t len)
{
    while (len--)
        printf("%d ", *arr++);
    printf("\n");
}

void printArr2(int **arr, size_t len1, size_t len2)
{
    while (len1--)
        printArr(*arr++, len2);
}

void rfree(void **val, size_t len)
{
    for (int i = 0; i < len; ++i)
        free(val[i]);
    free(val);
}
