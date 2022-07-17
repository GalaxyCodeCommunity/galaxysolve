#include <stdint.h>
#include <stdio.h>

typedef enum
{
    TT_ERROR = -1,
    TT_FREED = 0,
    TT_END = 0,
    TT_STRING,
    TT_INTEGER,
    TT_UNSIGNED_INTEGER,
    TT_OBJECT,
    TT_DECIMAL,
} TokenType;

typedef enum
{
    TI_ERROR = -1,
    TI_NULL = 0,
    TI_WHITESPACE,
    TI_INTEGER,
    TI_DECIMAL,
    TI_BOOL,
    TI_CHAR,
    TI_STRING,
    TI_SELF,
    TI_OR,
    TI_ANY,
    TI_ALPHA,
    TI_ALPHANUM,
    TI_DIGIT,
    TI_TAKEWHILE,
    TI_CHARFROM,
    TI_LAST,
} TokenId;

// error codes
#define PE_NOERROR 0ULL
#define PE_NOMATCH 1ULL
#define PE_WRONGOBJ 2ULL
#define PE_OBJNULL 3ULL
#define PE_DATAEND 4ULL
#define PE_NONUM 5ULL
#define PE_NOBOOL 6ULL
#define PE_WRONGMATCH 7ULL
#define PE_NOMEM 8ULL
#define PE_UNEXPECTED 9ULL
#define PE_NOOPTION 10ULL
#define PE_LAST 11ULL

#define OT_LAST 8

// structs

typedef void (*FreeFun)(void**);

typedef struct String
{
    char *c;
    size_t len;
    _Bool shouldFree;
} String;

typedef struct Object
{
    int id;
    FreeFun freeFun;
    void* obj;
} Object;

typedef struct Token
{
    TokenType type;
    size_t pos;
    int id;
    union
    {
        intmax_t integer;
        uintmax_t uinteger;
        double decimal;
        String string;
        Object obj;
    };
} Token;

typedef struct ParserState ParserState;
typedef Token (*ParseFunPointer)(Object*, ParserState*);

typedef struct ParseFun
{
    ParseFunPointer fun;
    Object obj;
    _Bool multicall;
} ParseFun;

typedef struct Parser
{
    ParseFun **funcs;
    size_t funCount;
} Parser;

struct ParserState
{
    Parser *parser;
    String data;
    size_t dataPos;
    int *pattern;
    size_t patLen;
    size_t patPos;
};

typedef _Bool (*CharPredicate)(Object*, char c);

#define strCreateLit(str) strCreate(str, sizeof(str) - 1, 0)

ParseFun *pfWhitespaces(_Bool skip);
ParseFun *pfInteger(_Bool skip);
ParseFun *pfDecimal(_Bool skip);
ParseFun *pfBool(_Bool skip);
ParseFun *pfChar(_Bool skip, char chr);
ParseFun *pfString(_Bool skip, String str);
ParseFun *pfSelf();
ParseFun *pfOr(ParseFun *f1, ParseFun *f2, _Bool shouldFree);
ParseFun *pfAny(ParseFun **funs, size_t funsLen, _Bool shouldFree);
ParseFun *pfTakeWhile(_Bool skip, CharPredicate fun, Object obj);
ParseFun *pfCharFrom(_Bool skip, String chars);

_Bool twAlpha(Object* obj, char c);
_Bool twAlphaNum(Object* obj, char c);
_Bool twDigit(Object* obj, char c);

// library functions
Token psNext(ParserState* ps);
ParserState psCreate(Parser *p, String data, int *pattern, size_t patLen);

_Bool parserTryGetFun(Parser *p, ParseFun **pf, int id);
void parserFree(Parser *p);
Parser parserCreate(ParseFun **funcs, size_t funCount);

void tokenPrint(FILE *out, Token t);
void tiPrint(FILE *out, TokenId ti);
void erPrint(FILE *out, int errCode);

void tokenFree(Token *t);
Token tokenDecimal(double num, int id, size_t pos);
Token tokenInteger(intmax_t num, int id, size_t pos);
Token tokenString(String s, int id, size_t pos);
Token tokenError(uintmax_t errorCode, size_t pos);
Token nullToken();

void strFree(String *str);
_Bool strEquals(String str1, String str2);
_Bool strContains(String str, char c);
String strCreateC(char *str);
String strCreate(char *str, size_t len, _Bool shouldFree);

void pfFree(ParseFun **pf);
void freePfs(ParseFun **pfs, size_t len);
Token pfInvoke(ParseFun *fun, ParserState *ps);
ParseFun *pfCreate(ParseFunPointer fun, Object obj, _Bool multicall);

void objFree(Object *obj);
Object objCreate(FreeFun freeFun, void *data, int id);
Object nullObj();

void freeIfNotNull(void **data);
void setNull(void **data);