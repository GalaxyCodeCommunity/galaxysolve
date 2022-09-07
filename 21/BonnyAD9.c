// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <inttypes.h>
#include <time.h>

uint32_t srngNext(uint64_t *state);
uint32_t rngNext();

int main()
{
    for (int i = 0; i < 100; ++i)
        printf("%u\n", rngNext() % 100);
}

uint32_t srngNext(uint64_t *state)
{
    *state ^= *state << 15;
    *state ^= *state >> 5;
    *state ^= *state << 13;
    return (*state >> 32) + (*state & 0xFFFFFFFF);
}

uint32_t rngNext()
{
    static uint64_t state;
    if (!state)
        state = time(NULL);
    return srngNext(&state);
}
