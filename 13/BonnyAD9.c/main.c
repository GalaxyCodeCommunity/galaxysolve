// compiled with 'clang -g -Wall -std=c17'

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Parser.h"

void cena(String str);
void email(String str);
void lisp(String str);

int main()
{
    /* Print format:
     * <index>:<data type>: <parser used>(<value>)[(<value in other format>)]
     */

    cena(strCreateLit("2000 Kc"));
    /* Cena:
     * 0:Integer: integer(2000)
     * 5:String: takewile("Kc")
     */

    email(strCreateLit("test123@example.com"));
    /* Email:
     * 0:String: takewile("test123")
     * 8:String: takewile("example.com")
     */

    lisp(strCreateLit("(* (+ 2 6) (- 6 (/ 4 2)))"));
    /* Email:
     * 0:Integer: char(40)('(')
     * 2:Integer: charform(42)('*')
     * 3:Integer: char(40)('(')
     * 5:Integer: charform(43)('+')
     * 6:Integer: integer(2)
     * 8:Integer: integer(6)
     * 9:Integer: char(41)(')')
     * 11:Integer: char(40)('(')
     * 13:Integer: charform(45)('-')
     * 14:Integer: integer(6)
     * 16:Integer: char(40)('(')
     * 18:Integer: charform(47)('/')
     * 19:Integer: integer(4)
     * 21:Integer: integer(2)
     * 22:Integer: char(41)(')')
     * 23:Integer: char(41)(')')
     * 24:Integer: char(41)(')')
     */
}

void cena(String str)
{
    printf("Cena:\n");

    // prepare parsing functions
    // you could also create your own parsing function
    ParseFun *pfs[] =
    {
        pfInteger(0),
        pfWhitespaces(1), // 1 indicates that it will be matched but not outputed as token
        pfTakeWhile(0, twAlpha, nullObj()),
    };
    const int flen = sizeof(pfs) / sizeof(ParseFun*);

    int pat[] = { 0, 1, 2 }; // indexes of parsing functions to use in order
    const int plen = sizeof(pat) / sizeof(int);

    // prepare parser
    Parser p = parserCreate(pfs, flen);
    ParserState ps = psCreate(&p, str, pat, plen);

    // parse the string
    Token t;
    while ((t = psNext(&ps)).type != TT_END)
    {
        tokenPrint(stdout, t); // print the token
        if (t.type == TT_ERROR) // exit on error (errors don't have to be freed)
            break;
        tokenFree(&t); // free the token
    }

    freePfs(pfs, flen); // free allocated memory
    printf("\n");
}

// prepare function taht determines whether given char can be in email
_Bool isEmailChar(Object *obj, char c)
{
    return c == '.' || c == '_' || isalnum(c);
}

void email(String str)
{
    printf("Email:\n");

    ParseFun *pfs[] =
    {
        pfTakeWhile(0, isEmailChar, nullObj()), // match any string of email chars
        pfChar(1, '@'), // match the '@' but skip it
    };
    const int flen = sizeof(pfs) / sizeof(ParseFun*);

    int pat[] = { 0, 1, 0 };
    const int plen = sizeof(pat) / sizeof(int);

    Parser p = parserCreate(pfs, flen);
    ParserState ps = psCreate(&p, str, pat, plen);

    Token t;
    while ((t = psNext(&ps)).type != TT_END)
    {
        tokenPrint(stdout, t);
        if (t.type == TT_ERROR)
            break;
        tokenFree(&t);
    }

    freePfs(pfs, flen);
    printf("\n");
}

void lisp(String str)
{
    printf("Email:\n");

    ParseFun *pfs[] =
    {
        pfChar(0, '('),
        pfCharFrom(0, strCreateLit("+-*/")), // matches any character from the string
        // pfSelf recursively matches the whole pattern
        pfOr(pfInteger(0), pfSelf(), 1), // matches a integer or self
        pfChar(0, ')'),
        pfWhitespaces(1),
    };
    const int flen = sizeof(pfs) / sizeof(ParseFun*);

    int pat[] = { 0, 1, 4, 2, 4, 2, 3 };
    const int plen = sizeof(pat) / sizeof(int);

    Parser p = parserCreate(pfs, flen);
    ParserState ps = psCreate(&p, str, pat, plen);

    Token t;
    while ((t = psNext(&ps)).type != TT_END)
    {
        tokenPrint(stdout, t);
        if (t.type == TT_ERROR)
            break;
        tokenFree(&t);
    }

    freePfs(pfs, flen);
    printf("\n");
}