// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <stdlib.h>

// Binary tree structures
typedef struct BTNode BTNode;

struct BTNode
{
    BTNode *left;
    BTNode *right;
    int value;
};

typedef void (*PassFun)(void *ct, int value);
// End of binary tree structures

// Stack structures
typedef struct SNode SNode;

struct SNode
{
    SNode *next;
    void *value;
};
// End of stack structures

void btReverse(BTNode **bt);
void btReverseNR(BTNode **bt); // not recursive version of btReverse
void printInt(FILE *out, int value);
// Binary tree functions
_Bool btAdd(BTNode **bt, int value);
BTNode **btFind(BTNode **bt, int value);
BTNode *btNodeCreate(int value, BTNode *left, BTNode *right);
BTNode **btCreate();
void btFree(BTNode **bt);
void btInorder(BTNode **bt, PassFun pf, void *pfct);
// Stack functions
void *stackPop(SNode **s);
_Bool stackPush(SNode **s, void *value);
SNode *sNodeCreate(void *value, SNode *next);
void stackFree(SNode **s);
SNode **stackCreate();

int main()
{
    // Binary tree is just double pointer to BTNode
    BTNode **bt = btCreate();
    btAdd(bt, 5);
    btAdd(bt, 9);
    btAdd(bt, 2);
    btAdd(bt, 6);
    btAdd(bt, 16);
    btAdd(bt, -89);

    btInorder(bt, (PassFun)printInt, stdout); // -89 2 5 6 9 16
    printf("\n");

    btReverse(bt); // recursive version

    btInorder(bt, (PassFun)printInt, stdout); // 16 9 6 5 2 -89
    printf("\n");

    btReverseNR(bt); // non recursive version

    btInorder(bt, (PassFun)printInt, stdout); // -89 2 5 6 9 16

    btFree(bt);
}

void btReverse(BTNode **bt)
{
    BTNode *n = *bt;
    if (!n)
        return;

    BTNode *h = n->left;
    n->left = n->right;
    n->right = h;

    btReverse(&n->left);
    btReverse(&n->right);
}

void btReverseNR(BTNode **bt)
{
    SNode **s = stackCreate();
    if (!s)
        return;

    BTNode *cur = *bt;

    while (cur || *s)
    {
        if (!cur)
            cur = stackPop(s);

        BTNode *h = cur->left;
        cur->left = cur->right;
        cur->right = h;

        if (cur->left)
            stackPush(s, cur->left);

        cur = cur->right;
    }

    stackFree(s);
}

void printInt(FILE *out, int value)
{
    fprintf(out, "%d ", value);
}

// Binary tree implementation

_Bool btAdd(BTNode **bt, int value)
{
    bt = btFind(bt, value);

    if (*bt) // the value is already in the tree
        return 0;

    BTNode *n = btNodeCreate(value, NULL, NULL);
    if (!n)
        return 0;

    *bt = n;
    return 1;
}

BTNode **btFind(BTNode **bt, int value)
{
    BTNode *n = *bt;
    if (!n || n->value == value)
        return bt;

    return n->value > value
        ? btFind(&n->left, value)
        : btFind(&n->right, value);
}

BTNode *btNodeCreate(int value, BTNode *left, BTNode *right)
{
    BTNode *n = malloc(sizeof(BTNode));
    if (!n)
        return NULL;

    n->left = left;
    n->right = right;
    n->value = value;

    return n;
}

BTNode **btCreate()
{
    return calloc(1, sizeof(BTNode *));
}

void btFree(BTNode **bt)
{
    BTNode *n = *bt;
    if (*bt)
    {
        btFree(&n->left);
        btFree(&n->right);
    }

    free(*bt);
}

void btInorder(BTNode **bt, PassFun pf, void *pfct)
{
    BTNode *n = *bt;
    if (!n)
        return;

    btInorder(&n->left, pf, pfct);
    pf(pfct, n->value);
    btInorder(&n->right, pf, pfct);
}

// stack implementation

void *stackPop(SNode **s)
{
    SNode *n = *s;
    if (!n)
        return NULL;
    *s = n->next;
    void *value = n->value;
    free(n);
    return value;
}

_Bool stackPush(SNode **s, void *value)
{
    SNode *n = sNodeCreate(value, *s);
    if (!n)
        return 0;

    *s = n;
    return 1;
}

SNode *sNodeCreate(void *value, SNode *next)
{
    SNode *n = malloc(sizeof(SNode));
    if (!n)
        return NULL;

    n->next = next;
    n->value = value;

    return n;
}

void stackFree(SNode **s)
{
    while (stackPop(s))
        ;
    free(s);
}

SNode **stackCreate()
{
    return calloc(1, sizeof(SNode *));
}
