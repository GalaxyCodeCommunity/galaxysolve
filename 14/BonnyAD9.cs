// .NET version: 6.0

using System.Text;

const char ch = '\ue001';

Console.WriteLine(Translate(".-|....|---|.---||.|")); // "ahoj e"

string Translate(ReadOnlySpan<char> str)
{
    Node morse = CreateMorse();
    StringBuilder sb = new();

    while (str.Length > 0)
    {
        if (str[0] == '|')
        {
            sb.Append(' ');
            str = str[1..];
            continue;
        }

        char c = FindChar(morse, ref str);
        switch (c)
        {
            case '\0':
                continue;
            case ch:
                sb.Append("ch");
                continue;
            default:
                sb.Append(c);
                continue;
        }
    }

    return sb.ToString();
}

char FindChar(Node? n, ref ReadOnlySpan<char> span)
{
    if (n is null || span.Length == 0)
        return '\0';

    char c = span[0];
    span = span[1..];

    return c switch
    {
        '|' => n.Char,
        '.' => FindChar(n.Dot, ref span),
        '-' => FindChar(n.Line, ref span),
        _ => '\0',
    };
}

Node CreateMorse() => new()
{
    Dot = new('e')
    {
        Dot = new('i')
        {
            Dot = new('s')
            {
                Dot = new('h')
                {
                    Dot = new('5'),
                    Line = new('4'),
                },
                Line = new('v')
                {
                    Dot = new('ŝ'),
                    Line = new('3'),
                },
            },
            Line = new('u')
            {
                Dot = new('f')
                {
                    Dot = new('é')
                },
                Line = new('ü')
                {
                    Dot = new('đ')
                    {
                        Dot = new('?'),
                        Line = new('_'),
                    },
                    Line = new('2'),
                },
            },
        },
        Line = new('a')
        {
            Dot = new('r')
            {
                Dot = new('l')
                {
                    Line = new('è')
                    {
                        Dot = new('"'),
                    },
                },
                Line = new('ä')
                {
                    Dot = new('+')
                    {
                        Line = new('.'),
                    },
                },
            },
            Line = new('w')
            {
                Dot = new('p')
                {
                    Dot = new('þ'),
                    Line = new('à')
                    {
                        Dot = new('@'),
                    },
                },
                Line = new('j')
                {
                    Dot = new('ĵ'),
                    Line = new('1')
                    {
                        Dot = new('\''),
                    },
                },
            },
        },
    },
    Line = new('t')
    {
        Dot = new('n')
        {
            Dot = new('d')
            {
                Dot = new('b')
                {
                    Dot = new('6')
                    {
                        Line = new('-'),
                    },
                    Line = new('='),
                },
                Line = new('x')
                {
                    Dot = new('/'),
                },
            },
            Line = new('k')
            {
                Dot = new('c')
                {
                    Dot = new('ç'),
                    Line = new()
                    {
                        Dot = new(';'),
                        Line = new('!'),
                    },
                },
                Line = new('y')
                {
                    Dot = new('(')
                    {
                        Line = new(')'),
                    },
                },
            },
        },
        Line = new('m')
        {
            Dot = new('g')
            {
                Dot = new('z')
                {
                    Dot = new('7'),
                    Line = new()
                    {
                        Line = new(','),
                    },
                },
                Line = new('q')
                {
                    Dot = new('ĝ'),
                    Line = new('ñ'),
                },
            },
            Line = new('o')
            {
                Dot = new('ö')
                {
                    Dot = new('8')
                    {
                        Dot = new(':'),
                    },
                },
                Line = new(ch)
                {
                    Dot = new('9'),
                    Line = new('0'),
                },
            },
        },
    },
};

record Node(char Char, Node? Dot, Node? Line)
{
    public Node(char chr) : this(chr, null, null) { }
    public Node() : this('\0') { }
}
