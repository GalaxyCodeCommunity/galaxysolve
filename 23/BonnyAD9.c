// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
//#include <math.h>

void caesar(char *str, int shift);
char caechar(char chr, int shift);
void bonusCZ(char *str);
int rate(const char *str);

int main()
{
    char msg[] = { "Ctypzn sdhipitrct sadjwn itmi." };
    bonusCZ(msg);
    printf("%s\n", msg); // Nejaky dostatecne dlouhy text.
}

void caesar(char *str, int shift)
{
    shift = shift % 26;

    for (; *str; ++str)
        *str = caechar(*str, shift);
}

char caechar(char chr, int shift)
{
    if (!isalpha(chr))
        return chr;

    const char off = isupper(chr) ? 'A' : 'a';

    return off + (26 + (chr - off) + shift) % 26;
}

void bonusCZ(char *str)
{
    int bs = 0;
    int br = INT_MIN;

    for (int i = 0; i < 26; ++i)
    {
        int r = rate(str);
        if (r > br)
        {
            bs = i;
            br = r;
        }
        caesar(str, 1);
    }

    caesar(str, bs);
}

int rate(const char *str)
{
#define LF_LEN 26
    // lf = lf - avg(lf)
    // cz letter frequencies so that the average is ~0 (less = less frequent)
    static int lf[] = 
    {
         6, -3, -3,  1, 9, -6, -6, -4, 2, -2,  1,  1,  0,
         7, 11,  0, -6, 1,  3,  5,  0, 3, -6, -6, -3, -2,
    };

    /* generating the values so that they are integers and the average is ~0
    float avg = 0;
    for (int i = 0; i < LF_LEN; ++i)
        avg += lf[i];
    avg /= LF_LEN;

    for (int i = 0; i< LF_LEN; ++i)
        printf("%d,\n", (int)roundf((lf[i] - avg) * 2));
    */

    int sum = 0;
    for (; *str; ++str)
    {
        if (!isalpha(*str))
            continue;

        sum += lf[isupper(*str) ? *str - 'A' : *str - 'a'];
    }
    return sum;
#undef LF_LEN
}
