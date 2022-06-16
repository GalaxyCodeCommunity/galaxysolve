// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

void swap(int* restrict const arr, const size_t length);
void printArr(const int* arr, const size_t length);

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    const int len = sizeof(arr) / sizeof(int);

    printArr(arr, len);
    swap(arr, len);
    printArr(arr, len);
}

void swap(int* restrict const arr, const size_t length)
{
    for (size_t i = 1; i < length; i += 2)
    {
        int h = arr[i - 1];
        arr[i - 1] = arr[i];
        arr[i] = h;
    }
}

void printArr(const int* arr, const size_t length)
{
    for (int i = 0; i < length; i++)
        printf("%d ", arr[i]);
    printf("\n");
}