// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct StrSpan
{
    char *str;
    size_t length;
} StrSpan;

typedef struct URI
{
    StrSpan scheme;
    StrSpan host;
    StrSpan port;
    StrSpan path;
    StrSpan query;
    StrSpan fragment;
} URI;

URI parseURI(char * const str);
StrSpan parseScheme(char * const str);
StrSpan parsePath(char *str);
StrSpan parsePort(char *str);
StrSpan parseHost(char *str);
StrSpan parseQuery(char *str);
StrSpan parseFragment(char *str);
void showURI(URI uri, FILE *f);
size_t printStrSpan(StrSpan span, FILE *f);

int main()
{
    URI uri = parseURI("https://localhost:8000/foo/baz?bar=baz");
    showURI(uri, stdout);
    /* > ./main
     * scheme: https
     * host: localhost
     * port: 8000
     * path: /foo/baz
     * query: bar=baz
     */
}

URI parseURI(char * const str)
{
    URI uri = { .scheme = parseScheme(str) };

    if (!uri.scheme.str)
        goto returnError;

    char *s = str + uri.scheme.length;
    if (*s++ != ':')
        goto returnError;

    if (*s != '/' || s[1] != '/')
    {
        uri.host.str = NULL;
        uri.host.length = 0;
        uri.port.str = NULL;
        uri.port.length = 0;
    }
    else
    {
        s += 2;
        uri.host = parseHost(s);
        s += uri.host.length;

        if (*s != ':')
        {
            uri.port.str = NULL;
            uri.port.length = 0;
        }
        else
        {
            uri.port = parsePort(++s);
            s += uri.port.length;
        }
    }

    uri.path = parsePath(s);
    s += uri.path.length;

    if (*s != '?')
    {
        uri.query.str = NULL;
        uri.query.length = 0;
    }
    else
    {
        uri.query = parseQuery(++s);
        s += uri.query.length;
    }

    if (*s != '#')
    {
        uri.fragment.str = NULL;
        uri.fragment.length = 0;
    }
    else
    {
        uri.fragment = parseFragment(++s);
        s += uri.fragment.length;
    }

    if (!*s)
        return uri;

returnError:
    uri.scheme.str = NULL;
    uri.scheme.length = 0;
    return uri;
}

StrSpan parseScheme(char * str)
{
    StrSpan span = { .str = str, .length = 0 };
    if (!str || !isalpha(*str))
    {
        span.str = NULL;
        span.length = 0;
        return span;
    }

    for (
        ;
        *str && (isalnum(*str) || *str == '+' || *str == '.' || *str == '-');
        ++str, ++span.length
    )
        ;

    return span;
}

StrSpan parsePath(char *str)
{
    StrSpan span = { .str = str, .length = 0 };

    if (!*str || *str != '/')
        return span;

    while (*++str && *str != '?' && *str != '#')
        ++span.length;
    ++span.length;

    return span;
}


StrSpan parsePort(char *str)
{
    StrSpan span = { .str = str, .length = 0 };

    for (; *str && *str != '/' && *str != '?' && *str != '#'; ++str)
        ++span.length;

    return span;
}

StrSpan parseHost(char *str)
{
    StrSpan span = { .str = str, .length = 0 };

    if (!*str)
        return span;

    if (*str == '[')
    {
        do ++span.length;
        while (*++str
            && *str != ']'
            && *str != ':'
            && *str != '/'
            && *str != '?'
            && *str != '#'
        );
        return span;
    }

    for (; *str
        && *str != ':'
        && *str != '/'
        && *str != '?'
        && *str != '#'
         ; ++str)
        ++span.length;

    return span;
}

StrSpan parseQuery(char *str)
{
    StrSpan span = { .str = str, .length = 0 };

    for (; *str && *str != '#'; ++str)
        ++span.length;

    return span;
}

StrSpan parseFragment(char *str)
{
    StrSpan span = { .str = str, .length = strlen(str) };
    return span;
}

void showURI(URI uri, FILE *f)
{
    fprintf(f, "scheme: ");
    printStrSpan(uri.scheme, f);
    fprintf(f, "\n");

    if (uri.host.str)
    {
        fprintf(f, "host: ");
        printStrSpan(uri.host, f);
        fprintf(f, "\n");

        if (uri.port.str)
        {
            fprintf(f, "port: ");
            printStrSpan(uri.port, f);
            fprintf(f, "\n");
        }
    }

    fprintf(f, "path: ");
    printStrSpan(uri.path, f);
    fprintf(f, "\n");

    if (uri.query.str)
    {
        fprintf(f, "query: ");
        printStrSpan(uri.query, f);
        fprintf(f, "\n");
    }

    if (uri.fragment.str)
    {
        fprintf(f, "fragment: ");
        printStrSpan(uri.fragment, f);
        fprintf(f, "\n");
    }
}

size_t printStrSpan(StrSpan span, FILE *f)
{
    return fwrite(span.str, sizeof(char), span.length, f);
}
