#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE (10)

static const char *coder[] = {
    ".-",    // A
    "-...",  // B
    "-.-.",  // C
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--..",  // Z
};

char m_to_c(char *m) {
    static const int count = sizeof(coder) / sizeof(coder[0]);
    for (int x = 0; x < count; x++)
        if (!strcmp(m, coder[x]))
            return x + 'a';
    return '?';
}

void decode(char *c) {
    char buffer[BUFFER_SIZE];
    int bcount = 0;
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '|') {
            printf("%c", m_to_c(&buffer));
            bcount = 0;
            memset(&buffer, '\0', sizeof(char) * BUFFER_SIZE);
        } else {
            if (!(bcount < (BUFFER_SIZE - 1))) {
                printf("%c", m_to_c(&buffer));
                bcount = 0;
                memset(&buffer, '\0', sizeof(char) * BUFFER_SIZE);
            } else {
                buffer[bcount] = c[i];
                bcount++;
            }
        }
    }
    printf("%c\n", m_to_c(&buffer));
}

int main() {
    decode(".-.|.|..-|...|.|-.-");
    return 0;
}
