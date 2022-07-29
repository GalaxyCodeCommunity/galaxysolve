// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CH '`'

typedef struct Node Node;

struct Node
{
    char chr;
    Node *dot;
    Node *line;
};

void translate(char *str, char *out);
char findChar(Node *n, char **str);
Node *makeMorse();
Node *nodeCreate(char chr, Node *dot, Node *line);
void nodeFree(Node **n);

int main()
{
    char mc[] = { ".-|....|---|.---||.|" };

    translate(mc, mc);

    printf("%s", mc); // "ahoj e"
}

void translate(char *str, char *out)
{
    Node *m = makeMorse();
    assert(m);

    while (*str)
    {
        if (*str == '|')
        {
            *out++ = ' ';
            str++;
            continue;
        }

        char c = findChar(m, &str);
        switch (c)
        {
        case 0:
            break;
        case CH:
            *out++ = 'c';
            *out++ = 'h';
            break;
        default:
            *out++ = c;
            break;
        }
    }
    nodeFree(&m);

    *out = 0;
}

char findChar(Node *n, char **str)
{
    if (!n || !**str)
        return 0;
    
    switch (*(*str)++)
    {
        case '.':
            return findChar(n->dot, str);
        case '-':
            return findChar(n->line, str);
        case '|':
            return n->chr;
        default:
            return 0;
    }
}

Node *makeMorse()
{
    return nodeCreate(0,
        nodeCreate('e',
            nodeCreate('i',
                nodeCreate('s',
                    nodeCreate('h',
                        nodeCreate('5',
                            NULL,
                            NULL
                        ),
                        nodeCreate('4',
                            NULL,
                            NULL
                        )
                    ),
                    nodeCreate('v',
                        NULL,
                        nodeCreate('3',
                            NULL,
                            NULL
                        )
                    )
                ),
                nodeCreate('u',
                    nodeCreate('f',
                        NULL,
                        NULL
                    ),
                    nodeCreate(0,
                        nodeCreate(0,
                            nodeCreate('?',
                                NULL,
                                NULL
                            ),
                            nodeCreate('_',
                                NULL,
                                NULL
                            )
                        ),
                        nodeCreate('2',
                            NULL,
                            NULL
                        )
                    )
                )
            ),
            nodeCreate('a',
                nodeCreate('r',
                    nodeCreate('l',
                        NULL,
                        nodeCreate(0,
                            nodeCreate('"',
                                NULL,
                                NULL
                            ),
                            NULL
                        )
                    ),
                    nodeCreate(0,
                        nodeCreate('+',
                            NULL,
                            nodeCreate('.',
                                NULL,
                                NULL
                            )
                        ),
                        NULL
                    )
                ),
                nodeCreate('w',
                    nodeCreate('p',
                        NULL,
                        nodeCreate(0,
                            nodeCreate('@',
                                NULL,
                                NULL
                            ),
                            NULL
                        )
                    ),
                    nodeCreate('j',
                        NULL,
                        nodeCreate('1',
                            nodeCreate('\'',
                                NULL,
                                NULL
                            ),
                            NULL
                        )
                    )
                )
            )
        ),
        nodeCreate('t',
            nodeCreate('n',
                nodeCreate('d',
                    nodeCreate('b',
                        nodeCreate('6',
                            NULL,
                            nodeCreate('-',
                                NULL,
                                NULL
                            )
                        ),
                        nodeCreate('=',
                            NULL,
                            NULL
                        )
                    ),
                    nodeCreate('x',
                        nodeCreate('/',
                            NULL,
                            NULL
                        ),
                        NULL
                    )
                ),
                nodeCreate('k',
                    nodeCreate('c',
                        NULL,
                        nodeCreate(0,
                            nodeCreate(';',
                                NULL,
                                NULL
                            ),
                            nodeCreate('!',
                                NULL,
                                NULL
                            )
                        )
                    ),
                    nodeCreate('y',
                        nodeCreate('(',
                            NULL,
                            nodeCreate(')',
                                NULL,
                                NULL
                            )
                        ),
                        NULL
                    )
                )
            ),
            nodeCreate('m',
                nodeCreate('g',
                    nodeCreate('z',
                        nodeCreate('7',
                            NULL,
                            NULL
                        ),
                        nodeCreate(0,
                            NULL,
                            nodeCreate(',',
                                NULL,
                                NULL
                            )
                        )
                    ),
                    nodeCreate('q',
                        NULL,
                        NULL
                    )
                ),
                nodeCreate('o',
                    nodeCreate(0,
                        nodeCreate('8',
                            nodeCreate(':',
                                NULL,
                                NULL
                            ),
                            NULL
                        ),
                        NULL
                    ),
                    nodeCreate(CH,
                        nodeCreate('9',
                            NULL,
                            NULL
                        ),
                        nodeCreate('0',
                            NULL,
                            NULL
                        )
                    )
                )
            )
        )
    );
}

Node *nodeCreate(char chr, Node *dot, Node *line)
{
    Node *n = malloc(sizeof(Node));
    assert(n);

    n->chr = chr;
    n->dot = dot;
    n->line = line;

    return n;
}

void nodeFree(Node **n)
{
    if (!*n)
        return;
    
    nodeFree(&(**n).dot);
    nodeFree(&(**n).line);

    free(*n);
    *n = NULL;
}
