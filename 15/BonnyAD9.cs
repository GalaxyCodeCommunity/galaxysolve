using System.Text;

Console.WriteLine(Translate("ahoj")); // --[-->+<]--------[-------->-<]>+.>--[-->+<]---[----------->-<]>.>--[-->+<]>----------------.>--[-->+<]>---------------------.>

static string Translate(string str) => str.Aggregate(new StringBuilder(), TranslateChar).ToString();

static StringBuilder TranslateChar(StringBuilder sb, char c) => DoNext(sb, c, '+').Append(".>");

static StringBuilder DoNext(StringBuilder sb, int count, char op)
{
    if (count <= 21)
        return sb.Append('>').Append(op, count);

    int sl = 255 / count;
    int mc = 255 % sl;

    sb.Append('-', mc)
      .Append("-[")
      .Append('-', sl)
      .Append('>')
      .Append(op)
      .Append("<]");

    return DoNext(sb, (255 - mc) / sl - count, op == '-' ? '+' : '-');
}
