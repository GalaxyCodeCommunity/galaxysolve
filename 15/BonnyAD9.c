// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>

void translateString(FILE *out, char *str);
void translateChar(FILE *out, char c);
void doNext(FILE *out, int count, char op);
void repeat(FILE *out, char c, int count);

int main()
{
    translateString(stdout, "ahoj"); // --[-->+<]--------[-------->-<]>+.>--[-->+<]---[----------->-<]>.>--[-->+<]>----------------.>--[-->+<]>---------------------.>
}

void translateString(FILE *out, char *str)
{
    while (*str)
        translateChar(out, *str++);
}

// still quite inefficient but much better than just repeating +
void translateChar(FILE *out, char c)
{
    doNext(out, c, '+');
    fputs(".>", out);
}

void doNext(FILE *out, int count, char op)
{
    if (count <= 21)
    {
        fputc('>', out);
        repeat(out, op, count);
        return;
    }
    
    const int sl = 255 / count;
    const int mc = 255 % sl;
    const int fix = (255 - mc) / sl - count;

    repeat(out, '-', mc);

    fputs("-[", out);
    repeat(out, '-', sl);
    fprintf(out, ">%c<]", op);

    doNext(out, fix, op == '-' ? '+' : '-');
}

void repeat(FILE *out, char c, int count)
{
    while (count--)
        fputc(c, out);
}
