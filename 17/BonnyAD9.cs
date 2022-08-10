// .NET version: 6.0

Console.WriteLine(MostUsedAlpha("párek v rohlíku")); // r

static char MostUsedAlpha(string s)
{
    Dictionary<char, int> counts = new();

    foreach (var c in s)
    {
        if (!char.IsLetter(c))
            continue;

        if (counts.ContainsKey(c))
            counts[c]++;
        else
            counts[c] = 0;
    }

    return counts.MaxBy(p => p.Value).Key;
}
