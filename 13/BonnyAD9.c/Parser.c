#include "Parser.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>

#define OT_NULL 0
#define OT_CASTBOOL 1
#define OT_CHARBOOL 2
#define OT_STRBOOL 3
#define OT_SELFSTRUCT 4
#define OT_ORTRUCT 5
#define OT_ANYSTRUCT 6
#define OT_TAKEWHILESTRUCT 7


// structs for parsing functions

typedef struct _CharBool
{
    char c;
    _Bool b;
} _CharBool;

typedef struct _StrBool
{
    String str;
    _Bool b;
} _StrBool;

typedef struct _SelfStruct
{
    ParserState ps;
    ParseFun *pf;
    ParseFun *self;
    _Bool init;
} _SelfStruct;

typedef struct _OrStruct
{
    ParseFun *pf1;
    ParseFun *pf2;
    ParseFun *mcpf;
    ParseFun *pf;
    ParseFun *self;
    _Bool shouldFree;
} _OrStruct;

typedef struct _AnyStruct
{
    ParseFun **pfs;
    size_t pfCount;
    ParseFun *mcpf;
    ParseFun *pf;
    ParseFun *self;
    _Bool shouldFree;
} _AnyStruct;

typedef struct _TakeWhileStruct
{
    CharPredicate predicate;
    Object obj;
    _Bool skip;
} _TakeWhileStruct;


// parsing functions

Token _pfWhitespaces(Object* obj, ParserState *ps);
Token _pfInteger(Object* obj, ParserState *ps);
Token _pfDecimal(Object* obj, ParserState *ps);
Token _pfBool(Object* obj, ParserState *ps);
Token _pfChar(Object* obj, ParserState *ps);
Token _pfString(Object* obj, ParserState *ps);
Token _pfSelf(Object* obj, ParserState *ps);
Token _pfOr(Object* obj, ParserState *ps);
Token _pfAny(Object* obj, ParserState *ps);
Token _pfTakeWhile(Object* obj, ParserState *ps);
Token _pfCharFrom(Object* obj, ParserState *ps);

Token _psNext(ParserState* ps);


// functions for freeing the parsing structs

void free_AnyStruct(void **data);
void free_OrStruct(void **data);
void free_SelfStruct(void **data);
void free_StrBool(void **data);
void free_TakeWhileStruct(void **data);


// implementation of parsing functinos

Token _pfWhitespaces(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_CASTBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _Bool skip = (_Bool)obj->obj;

    size_t s = ps->dataPos;
    while (ps->dataPos <= ps->data.len && isspace(ps->data.c[ps->dataPos]))
        ++ps->dataPos;

    if (skip)
        return nullToken();

    return tokenString(strCreate(ps->data.c + s, ps->dataPos - s, 0), TI_WHITESPACE, s);
}

Token _pfInteger(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_CASTBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _Bool skip = (_Bool)obj->obj;

    char* endptr;
    long long num = strtol(ps->data.c + ps->dataPos, &endptr, 10);

    if (endptr == ps->data.c + ps->dataPos)
        return tokenError(PE_NONUM, ps->dataPos);

    if (skip)
    {
        ps->dataPos = endptr - ps->data.c;
        return nullToken();
    }

    Token t = tokenInteger(num, TI_INTEGER, ps->dataPos);

    ps->dataPos = endptr - ps->data.c;

    return t;
}

Token _pfDecimal(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_CASTBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _Bool skip = (_Bool)obj->obj;

    char* endptr;
    double num = strtof(ps->data.c + ps->dataPos, &endptr);

    if (endptr == ps->data.c)
        return tokenError(PE_NONUM, ps->dataPos);

    if (skip)
    {
        ps->dataPos = endptr - ps->data.c;
        return nullToken();
    }

    Token t = tokenDecimal(num, TI_DECIMAL, ps->dataPos);

    ps->dataPos = endptr - ps->data.c;

    return t;
}

Token _pfBool(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_CASTBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _Bool skip = (_Bool)obj->obj;

    _Bool val;
    if (ps->dataPos + 5 < ps->data.len && strEquals(strCreate(ps->data.c + ps->dataPos, 5, 0), strCreateLit("false")))
        val = 0;
    else if (ps->dataPos + 4 < ps->data.len && strEquals(strCreate(ps->data.c + ps->dataPos, 4, 0), strCreateLit("true")))
        val = 1;
    else
        return tokenError(PE_NOBOOL, ps->dataPos);

    if (skip)
    {
        ps->dataPos += val ? 4 : 5;
        return nullToken();
    }

    Token t = tokenInteger(val, TI_BOOL, ps->dataPos);

    ps->dataPos += val ? 4 : 5;

    return t;
}

Token _pfChar(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_CHARBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    if (ps->dataPos >= ps->data.len)
        return tokenError(PE_DATAEND, ps->dataPos);

    _CharBool *cb = obj->obj;

    if (ps->data.c[ps->dataPos] != cb->c)
        return tokenError(PE_WRONGMATCH, ps->dataPos);

    ++ps->dataPos;

    if (cb->b)
        return nullToken();

    Token t = tokenInteger(cb->c, TI_CHAR, ps->dataPos - 1);

    return t;
}

Token _pfString(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_STRBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _StrBool *sb = obj->obj;

    if (ps->dataPos + sb->str.len <= ps->data.len || !strEquals(strCreate(ps->data.c + ps->dataPos, sb->str.len, 0), sb->str))
        return tokenError(PE_WRONGMATCH, ps->dataPos);

    ps->dataPos += sb->str.len;

    if (sb->b)
        return nullToken();

    Token t = tokenString(sb->str, TI_STRING, ps->dataPos - sb->str.len);

    return t;
}

Token _pfSelf(Object* obj, ParserState *ps)
{
    if (obj->id != OT_SELFSTRUCT)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _SelfStruct *ss = obj->obj;
    if (ss->init) // initialize on the first call of this instance
    {
        ss->ps.data = ps->data;
        ss->ps.dataPos = ps->dataPos;
        ss->ps.parser = ps->parser;
        ss->ps.patLen = ps->patLen;
        ss->ps.patPos = 0;
        ss->ps.pattern = ps->pattern;
        ss->pf = pfSelf();
        ((_SelfStruct*)ss->pf->obj.obj)->self = ss->self;
        ss->init = 0;
    }

    ParseFun self = *ss->self;
    *ss->self = *ss->pf; // swap the this instance with new one so that it doesn't interfere with the this one

    Token t = psNext(&ss->ps);

    *ss->self = self; // swap the instance back

    if (t.type == TT_FREED || t.type == TT_ERROR)
    { // finalize on the last call to this instance
        if (t.type != TT_ERROR)
            ps->dataPos = ss->ps.dataPos;
        pfFree(&ss->pf);
        ss->init = 1;
        ++ps->patPos; // move to next parser
    }

    return t;
}

Token _pfOr(Object* obj, ParserState *ps)
{
    if (obj->id != OT_ORTRUCT)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _OrStruct *os = obj->obj;

    if (!os->pf)
    {
        os->pf = pfOr(os->pf1, os->pf2, 0);
        ((_OrStruct*)os->pf->obj.obj)->self = os->self;
    }

    ParseFun self = *os->self;
    *os->self = *os->pf;
    Token t;

    if (os->mcpf)
    {
        t = pfInvoke(os->mcpf, ps);
        *os->self = self;
        if (t.type == TT_END || t.type == TT_ERROR)
        {
            pfFree(&os->pf);
            os->mcpf = NULL;
        }
        return t;
    }

    t = pfInvoke(os->pf1, ps);
    if (t.type == TT_ERROR)
    {
        --ps->patPos;
        t = pfInvoke(os->pf2, ps);
        *os->self = self;
        if (os->pf2->multicall && t.type != TT_END && t.type != TT_ERROR)
            os->mcpf = os->pf2;
        else
            pfFree(&os->pf);
    }
    else if (os->pf1->multicall && t.type != TT_END && t.type != TT_ERROR)
    {
        os->mcpf = os->pf1;
        *os->self = self;
    }
    else
    {
        *os->self = self;
        pfFree(&os->pf);
    }

    if (t.type == TT_ERROR)
        return tokenError(PE_NOOPTION, ps->dataPos);

    return t;
}

Token _pfAny(Object* obj, ParserState *ps)
{
    if (obj->id != OT_ANYSTRUCT)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    ++ps->patPos;
    _AnyStruct *as = obj->obj;

    if (!as->pf)
    {
        as->pf = pfAny(as->pfs, as->pfCount, 0);
        ((_AnyStruct*)as->pf->obj.obj)->self = as->self;
    }

    ParseFun self = *as->self;
    *as->self = *as->pf;
    Token t;

    if (as->mcpf)
    {
        t = pfInvoke(as->mcpf, ps);
        *as->self = self;
        if (t.type == TT_END || t.type == TT_ERROR)
        {
            pfFree(&as->pf);
            as->mcpf = NULL;
        }
        return t;
    }

    size_t i = 0;
    do
    {
        --ps->patPos;
        t = pfInvoke(as->pfs[i], ps);
        ++i;
    } while (t.type == TT_ERROR && i < as->pfCount);

    if (i == as->pfCount)
        return tokenError(PE_NOOPTION, ps->dataPos);

    *as->self = self;

    if (as->pfs[i]->multicall && t.type != TT_END && t.type != TT_ERROR)
        as->mcpf = as->pfs[i];

    return t;
}

Token _pfTakeWhile(Object* obj, ParserState *ps)
{
    ps->patPos++;

    if (obj->id != OT_TAKEWHILESTRUCT)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _TakeWhileStruct *tws = obj->obj;

    size_t s = ps->dataPos;
    while (ps->dataPos <= ps->data.len && tws->predicate(&tws->obj, ps->data.c[ps->dataPos]))
        ++ps->dataPos;
    
    if (s == ps->dataPos)
        return tokenError(PE_WRONGMATCH, ps->dataPos);

    if (tws->skip)
        return nullToken();

    return tokenString(strCreate(ps->data.c + s, ps->dataPos - s, 0), TI_TAKEWHILE, s);
}

Token _pfCharFrom(Object* obj, ParserState *ps)
{
    ++ps->patPos;

    if (obj->id != OT_STRBOOL)
        return tokenError(PE_WRONGOBJ, ps->dataPos);

    _StrBool *sb = obj->obj;

    if (ps->dataPos >= ps->data.len || !strContains(sb->str, ps->data.c[ps->dataPos]))
        return tokenError(PE_WRONGMATCH, ps->dataPos);

    ++ps->dataPos;

    if (sb->b)
        return nullToken();

    return tokenInteger(ps->data.c[ps->dataPos - 1], TI_CHARFROM, ps->dataPos);
}


// predicates for TakeWhile parsing functions

_Bool twAlpha(Object* obj, char c)
{
    return isalpha(c);
}

_Bool twAlphaNum(Object* obj, char c)
{
    return isalnum(c);
}

_Bool twDigit(Object* obj, char c)
{
    return isdigit(c);
}


// creates delegates for parsing functions

ParseFun *pfWhitespaces(_Bool skip)
{
    return pfCreate(_pfWhitespaces, objCreate(setNull, (void*)skip, OT_CASTBOOL), 0);
}

ParseFun *pfInteger(_Bool skip)
{
    return pfCreate(_pfInteger, objCreate(setNull, (void*)skip, OT_CASTBOOL), 0);
}

ParseFun *pfDecimal(_Bool skip)
{
    return pfCreate(_pfDecimal, objCreate(setNull, (void*)skip, OT_CASTBOOL), 0);
}

ParseFun *pfBool(_Bool skip)
{
    return pfCreate(_pfBool, objCreate(setNull, (void*)skip, OT_CASTBOOL), 0);
}

ParseFun *pfChar(_Bool skip, char chr)
{
    _CharBool *cb = malloc(sizeof(_CharBool));
    cb->b = skip;
    cb->c = chr;

    return pfCreate(_pfChar, objCreate(freeIfNotNull, cb, OT_CHARBOOL), 0);
}

ParseFun *pfString(_Bool skip, String str)
{
    _StrBool *sb = malloc(sizeof(_StrBool));
    sb->b = skip;
    sb->str = str;

    return pfCreate(_pfString, objCreate(free_StrBool, sb, OT_STRBOOL), 0);
}

ParseFun *pfSelf()
{
    ParseFun *pf = malloc(sizeof(ParseFun));
    pf->fun = _pfSelf;
    pf->multicall = 1;

    _SelfStruct *ss = malloc(sizeof(_SelfStruct));
    ss->init = 1;
    ss->self = pf;

    pf->obj = objCreate(free_SelfStruct, ss, OT_SELFSTRUCT);

    return pf;
}

ParseFun *pfOr(ParseFun *f1, ParseFun *f2, _Bool shouldFree)
{
    ParseFun *pf = malloc(sizeof(ParseFun));
    pf->fun = _pfOr;
    pf->multicall = 1;

    _OrStruct *os = malloc(sizeof(_OrStruct));
    os->pf1 = f1;
    os->pf2 = f2;
    os->mcpf = NULL;
    os->pf = NULL;
    os->self = pf;
    os->shouldFree = shouldFree;
    pf->obj = objCreate(free_OrStruct, os, OT_ORTRUCT);

    return pf;
}

ParseFun *pfAny(ParseFun **funs, size_t funsLen, _Bool shouldFree)
{
    ParseFun *pf = malloc(sizeof(ParseFun));
    pf->fun = _pfOr;
    pf->multicall = 1;

    _AnyStruct *as = malloc(sizeof(_AnyStruct));
    as->pfCount = funsLen;
    as->pfs = funs;
    as->mcpf = NULL;
    as->pf = NULL;
    as->self = pf;
    as->shouldFree = shouldFree;
    pf->obj = objCreate(free_AnyStruct, as, OT_ANYSTRUCT);

    return pf;
}

ParseFun *pfTakeWhile(_Bool skip, CharPredicate fun, Object obj)
{
    _TakeWhileStruct *tws = malloc(sizeof(_TakeWhileStruct));
    tws->obj = obj;
    tws->predicate = fun;
    tws->skip = skip;

    return pfCreate(_pfTakeWhile, objCreate(free_TakeWhileStruct, tws, OT_TAKEWHILESTRUCT), 0);
}

ParseFun *pfCharFrom(_Bool skip, String chars)
{
    _StrBool *sb = malloc(sizeof(_StrBool));
    sb->str = chars;
    sb->b = skip;

    ParseFun *pf = malloc(sizeof(ParseFun));
    pf->fun = _pfCharFrom;
    pf->obj = objCreate(free_StrBool, sb, OT_STRBOOL);

    return pf;
}


// helper functions and API implementation

Token _psNext(ParserState* ps)
{
    if (ps->patPos == ps->patLen)
        return tokenError(PE_NOERROR, ps->dataPos);
    
    if (ps->dataPos == ps->data.len)
        return tokenError(PE_DATAEND, ps->dataPos);

    ParseFun *pf;
    if (!parserTryGetFun(ps->parser, &pf, ps->pattern[ps->patPos]))
        return tokenError(PE_NOMATCH, ps->dataPos);

    return pfInvoke(pf, ps);
}

Token psNext(ParserState* ps)
{
    Token t;
    do t = _psNext(ps);
    while (t.type == TT_FREED);
    
    return t.type == TT_ERROR && t.integer == PE_NOERROR
        ? nullToken()
        : t;
}

ParserState psCreate(Parser *p, String data, int *pattern, size_t patLen)
{
    ParserState ps =
    {
        .parser = p,
        .data = data,
        .dataPos = 0,
        .pattern = pattern,
        .patLen = patLen,
        .patPos = 0,
    };
    return ps;
}

_Bool parserTryGetFun(Parser *p, ParseFun **pf, int id)
{
    if (id >= p->funCount)
        return 0;
    *pf = p->funcs[id];
    return 1;
}

void parserFree(Parser *p)
{
    if (!p->funcs)
        return;
    p->funcs = NULL;
}

Parser parserCreate(ParseFun **funcs, size_t funCount)
{
    Parser p =
    {
        .funcs = funcs,
        .funCount = funCount,
    };
    return p;
}

void tokenPrint(FILE *out, Token t)
{
    switch (t.type)
    {
    case TT_ERROR:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "Error: ");
        erPrint(out, t.integer);
        break;
    case TT_FREED:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "NULL");
        break;
    case TT_STRING:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "String: ");
        tiPrint(out, t.id);
        fprintf(out, "(\"");
        fwrite(t.string.c, sizeof(char), t.string.len, out);
        fprintf(out, "\")");
        break;
    case TT_INTEGER:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "Integer: ");
        tiPrint(out, t.id);
        fprintf(out, "(%"PRIdMAX")", t.integer);
        if (t.id == TI_CHAR || t.id == TI_CHARFROM)
            fprintf(out, "('%c')", (char)t.integer);
        break;
    case TT_UNSIGNED_INTEGER:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "UInteger: ");
        tiPrint(out, t.id);
        fprintf(out, "(%"PRIuMAX")", t.uinteger);
        break;
    case TT_OBJECT:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "Object");
        break;
    case TT_DECIMAL:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "Decimal: ");
        tiPrint(out, t.id);
        fprintf(out, "(%lf)", t.decimal);
    default:
        fprintf(out, "%"PRIdMAX":", t.pos);
        fprintf(out, "Unknown(%d)", t.type);
        break;
    }
    fprintf(out, "\n");
}

void tiPrint(FILE *out, TokenId ti)
{
    switch (ti)
    {
    case TI_ERROR:
        fprintf(out, "error");
        return;
    case TI_NULL:
        fprintf(out, "NULL");
        return;
    case TI_WHITESPACE:
        fprintf(out, "whitespace");
        return;
    case TI_INTEGER:
        fprintf(out, "integer");
        return;
    case TI_DECIMAL:
        fprintf(out, "decimal");
        return;
    case TI_BOOL:
        fprintf(out, "bool");
        return;
    case TI_CHAR:
        fprintf(out, "char");
        return;
    case TI_STRING:
        fprintf(out, "string");
        return;
    case TI_SELF:
        fprintf(out, "self");
        return;
    case TI_OR:
        fprintf(out, "or");
        return;
    case TI_ANY:
        fprintf(out, "any");
        return;
    case TI_ALPHA:
        fprintf(out, "alpha");
        return;
    case TI_ALPHANUM:
        fprintf(out, "alphanum");
        return;
    case TI_DIGIT:
        fprintf(out, "digit");
        return;
    case TI_TAKEWHILE:
        fprintf(out, "takewile");
        return;
    case TI_CHARFROM:
        fprintf(out, "charform");
        return;
    default:
        fprintf(out, "unknown(%d)", ti);
        return;;
    }
}

void erPrint(FILE *out, int errCode)
{
    switch (errCode)
    {
    case PE_NOERROR:
        fprintf(out, "NOERROR");
        return;
    case PE_NOMATCH:
        fprintf(out, "NOMATCH");
        return;
    case PE_WRONGOBJ:
        fprintf(out, "WRONGOBJ");
        return;
    case PE_DATAEND:
        fprintf(out, "DATAEND");
        return;
    case PE_NONUM:
        fprintf(out, "NONUM");
        return;
    case PE_NOMEM:
        fprintf(out, "NOEMEM");
        return;
    case PE_NOBOOL:
        fprintf(out, "NOEMEM");
        return;
    case PE_WRONGMATCH:
        fprintf(out, "NOEMEM");
        return;
    case PE_UNEXPECTED:
        fprintf(out, "UNEXPECTED");
        return;
    case PE_NOOPTION:
        fprintf(out, "NOOPTION");
        return;
    default:
        fprintf(out, "unknown(%d)", errCode);
        return;
    }
}

void tokenFree(Token *t)
{
    switch (t->type)
    {
    case TT_FREED:
        return;
    case TT_STRING:
        strFree(&t->string);
        break;
    case TT_OBJECT:
        objFree(&t->obj);
        break;
    default:
        break;
    }
    t->type = TT_FREED;
}

Token tokenDecimal(double num, int id, size_t pos)
{
    Token t =
    {
        .type = TT_DECIMAL,
        .id = id,
        .pos = pos,
        .decimal = num,
    };
    return t;
}

Token tokenInteger(intmax_t num, int id, size_t pos)
{
    Token t =
    {
        .type = TT_INTEGER,
        .id = id,
        .pos = pos,
        .integer = num,
    };
    return t;
}

Token tokenString(String s, int id, size_t pos)
{
    Token t =
    {
        .type = TT_STRING,
        .id = id,
        .pos = pos,
        .string = s,
    };
    return t;
}

Token tokenError(uintmax_t errorCode, size_t pos)
{
    Token t =
    {
        .type = TT_ERROR,
        .id = TI_ERROR,
        .pos = pos,
        .uinteger = errorCode,
    };
    return t;
}

Token nullToken()
{
    Token t =
    {
        .type = TT_FREED,
        .id = TI_NULL,
    };
    return t;
}

void strFree(String *str)
{
    if (!str->c)
        return;
    if (str->shouldFree)
        free(str->c);
    str->c = NULL;
}

_Bool strEquals(String str1, String str2)
{
    if (str1.len != str2.len)
        return 0;

    return strncmp(str1.c, str2.c, str1.len) == 0;
}

_Bool strContains(String str, char c)
{
    for (size_t i = 0; i < str.len; i++)
    {
        if (str.c[i] == c)
            return 1;
    }
    return 0;
}

String strCreateC(char *str)
{
    return strCreate(str, strlen(str), 1);
}

String strCreate(char *str, size_t len, _Bool shouldFree)
{
    String s =
    {
        .c = str,
        .len = len,
        .shouldFree = shouldFree,
    };
    return s;
}

void pfFree(ParseFun **pf)
{
    if (!*pf)
        return;
    objFree(&(*pf)->obj);
    free(*pf);
    *pf = NULL;
}

void freePfs(ParseFun **pfs, size_t len)
{
    while (len--)
        pfFree(pfs++);
}

Token pfInvoke(ParseFun *fun, ParserState *ps)
{
    return fun->fun(&fun->obj, ps);
}

ParseFun *pfCreate(ParseFunPointer fun, Object obj, _Bool multicall)
{
    ParseFun *pf = malloc(sizeof(ParseFun));
    pf->fun = fun;
    pf->obj = obj;
    pf->multicall = multicall;
    return pf;
}

void objFree(Object *obj)
{
    if (obj->id == OT_NULL)
        return;
    obj->freeFun(&obj->obj);
    obj->id = OT_NULL;
}

Object objCreate(FreeFun freeFun, void *data, int id)
{
    Object obj =
    {
        .freeFun = freeFun,
        .obj = data,
        .id = id,
    };
    return obj;
}

Object nullObj()
{
    return objCreate(freeIfNotNull, NULL, OT_NULL);
}


// functions for freeing structs

void free_TakeWhileStruct(void **data)
{
    if (!*data)
        return;
    _TakeWhileStruct *tws = *data;
    objFree(&tws->obj);
    free(tws);
    *data = NULL;
}

void free_AnyStruct(void **data)
{
    if (!*data)
        return;
    _AnyStruct *as = *data;
    if (as->shouldFree)
        freePfs(as->pfs, as->pfCount);
    if (as->pf)
        pfFree(&as->pf);
    free(as);
    *data = NULL;
}

void free_OrStruct(void **data)
{
    if (!*data)
        return;
    _OrStruct *os = *data;
    if (os->shouldFree)
    {
        pfFree(&os->pf1);
        pfFree(&os->pf2);
    }
    if (os->pf)
        pfFree(&os->pf);
    free(os);
    *data = NULL;
}

void free_SelfStruct(void **data)
{
    if (!*data)
        return;
    _SelfStruct *ss = *data;
    if (!ss->init)
        pfFree(&ss->pf);
    free(ss);
    *data = NULL;
}

void free_StrBool(void **data)
{
    if (!*data)
        return;
    strFree(&((_StrBool*)*data)->str);
    free(*data);
    *data = NULL;
}

void freeIfNotNull(void **data)
{
    if (!*data)
        return;
    free(*data);
    *data = NULL;
}

void setNull(void **data)
{
    *data = NULL;
}