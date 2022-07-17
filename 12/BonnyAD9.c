// compiled with clang -Wall -g -std=c17

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Word
{
    int wid;
    char** shapes;
    size_t count;
} Word;


typedef struct Language
{
    char* id;
    Word* words;
    size_t count;
} Language;

typedef struct Translator
{
    Language* langs;
    size_t count;
} Translator;

const char* translate(const Translator* const tr, const char* const word, const char* const lng, int count);
int lnCmp(const void* s, const void* ln);
int wCmp(const void* sid, const void* wid);
Word* lnGetWord(const Language* const ln, const char* const word);
_Bool wordHasShape(const Word* const w, const char* const word);
int lnCmp(const void* s, const void* ln);
Translator trRead(FILE* const in);
Language lnRead(FILE* const in);
Word wordRead(FILE* const in);
char* shRead(FILE* const in);
void trFree(Translator* const restrict tr);
void lnFree(Language* const restrict ln);
void wordFree(Word* const restrict w);

int main()
{
    FILE* f;
    fopen_s(&f, "languages.txt", "r");
    Translator tr = trRead(f);
    fclose(f);

    printf("%s\n", translate(&tr, "dog", "cs", 0));
    printf("%s\n", translate(&tr, "cat", "cs", 2));
    printf("%s\n", translate(&tr, "human", "en", 10));

    trFree(&tr);
}

const char* translate(const Translator* const tr, const char* const word, const char* const lng, int count)
{
    if (count <= 0)
        count = 1;

    Language* ln = bsearch(lng, tr->langs, tr->count, sizeof(Language), lnCmp);
    if (!ln)
        return word;

    Word* w = NULL;
    for (size_t i = 0; !w && i < tr->count; i++)
        w = lnGetWord(tr->langs + i, word);

    if (!w)
        return word;

    Word* t = bsearch(&w->wid, ln->words, ln->count, sizeof(Word), wCmp);
    if (!t)
        return word;
    
    return count >= t->count ? t->shapes[0] : t->shapes[count];
}

int lnCmp(const void* s, const void* ln)
{
    return strcmp(s, ((Language*)ln)->id);
}

int wCmp(const void* sid, const void* wid)
{
    return *(int*)sid - *(int*)wid;
}

Word* lnGetWord(const Language* const ln, const char* const word)
{
    for (size_t i = 0; i < ln->count; i++)
    {
        if (wordHasShape(ln->words + i, word))
            return ln->words + i;
    }
    return NULL;
}

_Bool wordHasShape(const Word* const w, const char* const word)
{
    for (size_t i = 0; i < w->count; i++)
    {
        if (strcmp(word, w->shapes[i]) == 0)
            return 1;
    }
    return 0;
}

Translator trRead(FILE* const in)
{
    Translator tr;
    fscanf_s(in, " %zu", &tr.count);
    tr.langs = malloc(tr.count * sizeof(Language));
    assert(tr.langs);

    for (size_t i = 0; i < tr.count; i++)
        tr.langs[i] = lnRead(in);

    return tr;
}

Language lnRead(FILE* const in)
{
    Language ln = { .id = malloc(3 * sizeof(char)) };
    fscanf_s(in, " %2s %zu", ln.id, 3, &ln.count);
    ln.words = malloc(ln.count * sizeof(Word));
    assert(ln.words);

    for (size_t i = 0; i < ln.count; i++)
        ln.words[i] = wordRead(in);

    return ln;
}

Word wordRead(FILE* const in)
{
    Word w;
    fscanf_s(in, " %d %zu", &w.wid, &w.count);
    w.shapes = malloc(w.count * sizeof(char*));
    assert(w.shapes);

    for (size_t i = 0; i < w.count; i++)
        w.shapes[i] = shRead(in);

    return w;
}

char* shRead(FILE* const in)
{
    size_t len;
    fscanf_s(in, " %zu", &len);
    char* s = malloc(len * sizeof(char) + 1);
    assert(s);

    fscanf_s(in, " %s", s, len + 1);
    return s;
}

void trFree(Translator* const restrict tr)
{
    for (size_t i = 0; i < tr->count; i++)
        lnFree(tr->langs + i);
    free(tr->langs);
}

void lnFree(Language* const restrict ln)
{
    for (size_t i = 0; i < ln->count; i++)
        wordFree(ln->words + i);
    free(ln->words);
}

void wordFree(Word* const restrict w)
{
    for (size_t i = 0; i < w->count; i++)
        free(w->shapes[i]);
    free(w->shapes);
}

/* contents of languages.txt:
2
cs 3
  1 5
    3 psu
    3 pes
    3 psi
    3 psi
    3 psi
  2 5
    5 kocek
    5 kocka
    5 kocky
    5 kocky
    5 kocky
  3 5
    4 lidi
    6 človek
    4 lidi
    4 lidi
    4 lidi
en 3
  1 2
    4 dogs
    3 dog
  2 2
    4 cats
    3 cat
  3 2
    6 humans
    5 human
*/
