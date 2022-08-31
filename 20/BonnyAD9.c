// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LIST_START_SIZE 2
#define LIST_ALLOC_SIZE 16

typedef struct List
{
    int *data;
    size_t length;
    size_t allocated;
} List;

List decompose(int num);
void listAdd(List *l, int item);
void listFree(List *l);
List listCreate();
void listPrint(FILE* out, List l);

int main()
{
    List l = decompose(12);
    listPrint(stdout, l); // 2 2 3
    listFree(&l);
}

List decompose(int num)
{
    List l = listCreate();

    if (num <= 1)
    {
        listAdd(&l, num);
        return l;
    }

    for (int i = 2; num != 1; ++i)
    {
        while (num % i == 0)
        {
            listAdd(&l, i);
            num /= i;
        }
    }

    return l;
}

void listAdd(List *l, int item)
{
    if (l->length == l->allocated)
    {
        size_t newSize = l->allocated == 0
            ? 1
            : (l->allocated < LIST_ALLOC_SIZE
                ? l->allocated * 2
                : l->allocated + LIST_ALLOC_SIZE
            );
        int *newData = realloc(l->data, newSize);
        if (!newData)
            return;
        l->data = newData;
        l->allocated = newSize;
    }

    l->data[l->length] = item;
    ++l->length;
}

void listFree(List *l)
{
    if (!l->data)
        return;
    free(l->data);
    l->allocated = 0;
    l->length = 0;
    l->data = NULL;
}

List listCreate()
{
    List l =
    {
        .allocated = LIST_START_SIZE,
        .data = malloc(sizeof(int) * LIST_START_SIZE),
        .length = 0,
    };

    if (!l.data)
        l.allocated = 0;

    return l;
}

void listPrint(FILE* out, List l)
{
    for (size_t i = 0; i < l.length; ++i)
        fprintf(out, "%d ", l.data[i]);
}
