// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h> // FILE, stdout, fprintf
#include <limits.h> // CHAR_BIT, UCHAR_MAX
#include <assert.h> // assert
#include <string.h> // memcpy_s
#include <stdlib.h> // malloc, free

void radixSort(int * const arr, const size_t length);
void radixPass(
    int * const restrict arr,
    const size_t length,
    const size_t passNum,
    int * const restrict harr
);
void printArr(FILE *out, const int *arr, size_t length);

int main()
{
    int arr[] = { 5, 1, -3, 9, 6, 5, 0 };
    const int len = sizeof(arr) / sizeof(int);

    radixSort(arr, len);
    printArr(stdout, arr, len);
}

// time complexity:  O(n)
// space complexity: O(n)
void radixSort(int * const arr, const size_t length)
{
    // expects that integers are represented with two's complement

    // create array with arr and helper array
    int *arrs[] = { arr, malloc(sizeof(int) * length) };
    assert(arrs[1]);

    // order the array for each byte index
    for (size_t i = 0; i < sizeof(int); ++i)
        // when i is odd arr and helper array will swap
        radixPass(arrs[i & 1], length, i, arrs[!(i & 1)]);

    // in case that sizeof(int) is odd (it almost always won't)
    // the result is not in arr but in the helper array
    if (sizeof(int) & 1)
        memcpy_s(arr, length, arrs[1], length);
    free(arrs[1]);
}

// gets a byte from int with inversed sign bit (pass is LE byte index)
#define ORD_INT(num, pass) ((num ^ 1 << (sizeof(int) * CHAR_BIT - 1))\
    >> pass * CHAR_BIT & UCHAR_MAX)

// counting sort on one byte of the int
void radixPass(
    int * const restrict arr,
    const size_t length,
    const size_t passNum,
    int * const restrict harr
)
{
    size_t counts[UCHAR_MAX + 1] = { 0 };

    // count occurences of the byte from each int
    for (size_t i = 0; i < length; ++i)
        ++counts[ORD_INT(arr[i], passNum)];

    // change counts to be indexes in the result array
    size_t ps = 0;
    for (int i = 0; i <= UCHAR_MAX; ++i)
    {
        const size_t psh = ps;
        ps += counts[i];
        counts[i] = psh;
    }

    // reorder arr into harr
    for (size_t i = 0; i < length; ++i)
        harr[counts[ORD_INT(arr[i], passNum)]++] = arr[i];
}

#undef ORD_INT

void printArr(FILE *out, const int *arr, size_t length)
{
    while (length--)
        fprintf(out, "%d ", *arr++);
    fprintf(out, "\n");
}
