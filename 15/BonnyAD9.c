// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>

void translateString(FILE *out, char *str);
void translateChar(FILE *out, char c);

int main()
{
    translateString(stdout, "ahoj"); // --[-->+<]>------------------------------.>--[-->+<]>-----------------------.>--[-->+<]>----------------.>--[-->+<]>---------------------.>
}

void translateString(FILE *out, char *str)
{
    while (*str)
        translateChar(out, *str++);
}

// still quite inefficient but much better than just repeating +
void translateChar(FILE *out, char c)
{
    const int sl = 255 / c;
    int mc = 255 % sl;
    const int fix = (255 - mc) / sl - c;

    while (mc--)
        fputc('-', out);

    fputs("-[", out);

    mc = sl;
    while (mc--)
        fputc('-', out);

    fputs(">+<]>", out);

    mc = fix;
    while (mc--)
        fputc('-', out);

    fputs(".>", out);
}
