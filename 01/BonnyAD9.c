// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

void f(FILE* out, int num);

int main()
{
    printf("cislo: ");
    int n;
    scanf_s("%d", &n);

    f(stdout, n);
}

void f(FILE* out, int num)
{
    for (int i = 1; i < num; i++)
    {
        fprintf(out, "%d ", i);

        if (i % 3 == 0)
            fprintf(out, "fizz");
        if (i % 5 == 0)
            fprintf(out, "buzz");

        fprintf(out, "\n");
    }
}