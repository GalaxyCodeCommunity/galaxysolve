// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int *arr, size_t len);
void swap(int *a, int *b);
void printArr(FILE *out, int *arr, size_t len);

int main()
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const size_t len = sizeof(arr) / sizeof(int);

    srand(time(NULL));

    printArr(stdout, arr, len);
    shuffle(arr, len);
    printArr(stdout, arr, len);
}

void shuffle(int *arr, size_t len)
{
    for (; len; --len, ++arr)
        swap(arr, arr + rand() % len);
}

void swap(int *a, int *b)
{
    int h = *a;
    *a = *b;
    *b = h;
}

void printArr(FILE *out, int *arr, size_t len)
{
    while (len--)
        fprintf(out, "%d ", *arr++);
    fprintf(out, "\n");
}
