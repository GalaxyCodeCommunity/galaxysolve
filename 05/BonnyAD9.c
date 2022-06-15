// compiled with: clang -g -Wall -std=c17 -o res.exe BonnyAD9.c

#include <stdlib.h>
#include <stdio.h>

void printRange(FILE* out, int start, int end);

int main()
{
    printf("Napiste cisla: ");
    int s, e;
    scanf_s(" %d %d", &s, &e);

    printRange(stdout, s, e);
}

void printRange(FILE* out, int start, int end)
{
    int step = end - start;
    step = step / abs(step);

    int s = start, l = end;
    if (start > end)
    {
        s = end;
        l = start;
    }

    for (int i = start; i >= s && i <= l; i += step)
        fprintf(out, "%d ", i);
}