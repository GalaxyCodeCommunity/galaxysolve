// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

void reverse(int* const arr, const size_t length);
void printArr(FILE* const out, const int* const arr, const size_t length);

int main()
{
    const int length = 3;
    int arr[] = { 1, 2, 3 };

    printArr(stdout, arr, length);
    reverse(arr, length);
    printArr(stdout, arr, length);
}

void reverse(int* restrict arr, const size_t length)
{
    for (size_t i = 0; i < length / 2; i++)
    {
        int h = arr[i];
        arr[i] = arr[length - i - 1];
        arr[length - i - 1] = h;
    }
}

void printArr(FILE* const out, const int* const arr, const size_t length)
{
    fprintf(out, "[%d", *arr);

    for (size_t i = 1; i < length; i++)
        fprintf(out, ", %d", arr[i]);

    fprintf(out, "]\n");
}