using System.Collections;
using System.Text;

namespace GS13;

public class Program
{
    public static void Main(string[] args)
    {
        Parser p = new()
        {
            Parser.Int,
            Parser.Ignore(Parser.String(char.IsWhiteSpace)), // Parse.Ignore will match the given parse function, but ignore it in the result
            Parser.String(char.IsLetter)
        };
        Console.WriteLine(new ListToken(p.Parse("2000 Kč")));
        /* ListToken {
         *     IntToken { Index = 0, Length = 4, Ignore = False, Num = 2000 }
         *     StringToken { Index = 5, Length = 2, Ignore = False, Str = Kč }
         * }
         */

        var isEmailChar = bool (char p) => p == '_' || p == '.' || char.IsLetterOrDigit(p);
        p = new()
        {
            Parser.String(isEmailChar),
            Parser.Ignore(Parser.String("@")),
            Parser.String(isEmailChar),
        };
        Console.WriteLine(new ListToken(p.Parse("test123@example.com")));
        /* ListToken {
         *     StringToken { Index = 0, Length = 7, Ignore = False, Str = test123 }
         *     StringToken { Index = 8, Length = 11, Ignore = False, Str = example.com }
         * }
         */

        p = new()
        {
            Parser.Ignore(Parser.String("(")),
            Parser.String(p => !char.IsWhiteSpace(p)),
            Parser.Ignore(Parser.String(char.IsWhiteSpace)),
            Parser.Or(Parser.Int, Parser.Self), // Parser.Self recursively matches the whole pattern
            Parser.Ignore(Parser.String(char.IsWhiteSpace)),
            Parser.Or(Parser.Int, Parser.Self),
            Parser.Ignore(Parser.String(")")),
        };
        Console.WriteLine(new ListToken(p.Parse("(* (+ 2 6) (- 6 (/ 4 2)))")));
        /* ListToken {
         *     StringToken { Index = 1, Length = 1, Ignore = False, Str = * }
         *     ListToken {
         *         StringToken { Index = 1, Length = 1, Ignore = False, Str = + }
         *         IntToken { Index = 3, Length = 1, Ignore = False, Num = 2 }
         *         IntToken { Index = 5, Length = 1, Ignore = False, Num = 6 }
         *     }
         *     ListToken {
         *         StringToken { Index = 1, Length = 1, Ignore = False, Str = - }
         *         IntToken { Index = 3, Length = 1, Ignore = False, Num = 6 }
         *         ListToken {
         *             StringToken { Index = 1, Length = 1, Ignore = False, Str = / }
         *             IntToken { Index = 3, Length = 1, Ignore = False, Num = 4 }
         *             IntToken { Index = 5, Length = 1, Ignore = False, Num = 2 }
         *         }
         *     }
         * }
         */
    }
}

delegate IToken ParseFun(Parser p, ReadOnlySpan<char> span, int index);

class Parser : IEnumerable<ParseFun>
{
    public List<ParseFun> Parsers { get; } = new();

    public Parser() { }


    public List<IToken> Parse(string str) => Parse(str, out int _);

    public List<IToken> Parse(ReadOnlySpan<char> str, out int pos)
    {
        List<IToken> tokens = new();

        pos = 0;

        for (int i = 0; i < Parsers.Count; i++)
        {
            var t = Parsers[i](this, str[pos..], pos);
            pos += t.Length;
            if (!t.Ignore)
                tokens.Add(t);
        }

        return tokens;
    }

    public void Add(ParseFun f) => Parsers.Add(f);

    public IEnumerator<ParseFun> GetEnumerator() => ((IEnumerable<ParseFun>)Parsers).GetEnumerator();
    IEnumerator IEnumerable.GetEnumerator() => ((IEnumerable)Parsers).GetEnumerator();

    public static ParseFun Ignore(ParseFun f) => (p, sp, i) =>
    {
        var t = f(p, sp, i);
        return new IgnoredToken(t.Index, t.Length, true, t);
    };

    public static IntToken Int(Parser p, ReadOnlySpan<char> span, int index)
    {
        if (span.Length == 0 || !char.IsDigit(span[0]))
            throw new InvalidDataException("Expected integer");

        int pos = 0;
        long num = 0;

        for (; pos < span.Length && char.IsDigit(span[pos]); pos++)
            num = num * 10 + span[pos] - '0';

        return new(index, pos, false, num);
    }

    public static ParseFun String(string s) => (_, sp, i) => sp.StartsWith(s) ? new StringToken(i, s.Length, false, s) : throw new InvalidDataException($"Expected '{s}'");

    public static ParseFun String(Func<char, bool> p) => (_, sp, i) =>
    {
        int pos = 0;
        for (; pos < sp.Length && p(sp[pos]); pos++) ;
        return pos == 0 ? throw new InvalidDataException("Expected string matching predicate") : new StringToken(i, pos, false, sp[..pos].ToString());
    };

    public static ListToken Self(Parser p, ReadOnlySpan<char> sp, int index)
    {
        var l = p.Parse(sp, out int len);
        return new(index, len, false, l);
    }

    public static ParseFun Or(ParseFun f1, ParseFun f2) => (p, sp, i) =>
    {
        try
        {
            var t = f1(p, sp, i);
            return t;
        }
        catch (InvalidDataException)
        {
            try
            {
                var t = f2(p, sp, i);
                return t;
            }
            catch (InvalidDataException)
            {
                throw new InvalidDataException("No ParseFun matches");
            }
        }
    };

    public static FloatToken Float(Parser p, ReadOnlySpan<char> sp, int i)
    {
        if (sp.Length == 0 || !char.IsDigit(sp[0]))
            throw new InvalidDataException("Expected integer");

        int pos = 0;
        double num = 0;

        for (; pos < sp.Length && char.IsDigit(sp[pos]); pos++)
            num = num * 10 + sp[pos] - '0';

        if (pos >= sp.Length || sp[pos] != '.')
            return new(i, pos, true, num);

        pos++;
        for (int div = 10; pos < sp.Length && char.IsDigit(sp[pos]); pos++, div *= 10)
            num += (sp[pos] - '0') / div;

        return new(i, pos, true, num);
    }
}

public interface IToken
{
    public int Index { get; }
    public int Length { get; }
    public bool Ignore { get; }
}

public record IntToken(int Index, int Length, bool Ignore, long Num) : IToken;
public record StringToken(int Index, int Length, bool Ignore, string Str) : IToken;
public record CharToken(int Index, int Length, bool Ignore, char Chr) : IToken;
public record FloatToken(int Index, int Length, bool Ignore, double Num) : IToken;
public record IgnoredToken(int Index, int Length, bool Ignore, IToken Token) : IToken;
public record ListToken(int Index, int Length, bool Ignore, List<IToken> Tokens) : IToken
{
    public ListToken(List<IToken> tokens) : this(0, 0, false, tokens) { }

    public override string ToString()
    {
        StringBuilder sb = new();
        sb.AppendLine("ListToken {");
        foreach (var token in Tokens)
        {
            string[] ss = token.ToString()!.Split('\n');
            foreach (var s in ss)
                sb.Append("    ").AppendLine(s);
        }
        sb.Append('}');
        return sb.ToString();
    }
}
