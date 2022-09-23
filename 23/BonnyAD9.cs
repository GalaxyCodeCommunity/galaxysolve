// .NET version: 6.0

Console.WriteLine(BonusCZ("Ctypzn sdhipitrct sadjwn itmi.")); // Nejaky dostatecne dlouhy text.

string Caesar(string str, int shift)
{
    Span<char> chr = stackalloc char[str.Length];
    str.CopyTo(chr);
    CaesarSpan(chr, shift);
    return chr.ToString();
}

// this is here for optimizatons
void CaesarSpan(Span<char> str, int shift)
{
    shift %= 26;

    foreach (ref var c in str)
        c = Caechar(c, shift);
}

char Caechar(char c, int shift)
{
    if (!char.IsAscii(c) || !char.IsLetter(c))
        return c;

    int ul = char.IsUpper(c) ? 'A' : 'a';

    return (char)(ul + (26 + shift + c - ul) % 26);
}

string BonusCZ(string str)
{
    Span<char> chs = stackalloc char[str.Length];
    str.CopyTo(chs);

    int mi = 0;
    int ms = int.MinValue;
    for (int i = 0; i < 26; i++)
    {
        var s = Rate(chs);
        if (s > ms)
            (ms, mi) = (s, i);
        CaesarSpan(chs, 1);
    }

    CaesarSpan(chs, mi);
    return chs.ToString();
}

int Rate(ReadOnlySpan<char> str)
{
    // values are copied from my C version
    ReadOnlySpan<int> lf = stackalloc int[]
    {
         6, -3, -3,  1, 9, -6, -6, -4, 2, -2,  1,  1,  0,
         7, 11,  0, -6, 1,  3,  5,  0, 3, -6, -6, -3, -2,
    };

    var sum = 0;
    foreach (var c in str)
    {
        if (char.IsAscii(c) && char.IsLetter(c))
            sum += lf[char.IsUpper(c) ? c - 'A' : c - 'a'];
    }

    return sum;
}
