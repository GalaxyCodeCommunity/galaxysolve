// .NET version: 6.0

Console.Write("string: ");
Console.WriteLine(RevCase(Console.ReadLine()!));

static string RevCase(string s) => string.Concat(s.Select(c => c switch
{
    >= 'A' and <= 'Z' => (char)(c + 'a' - 'A'),
    >= 'a' and <= 'z' => (char)(c + 'A' - 'a'),
    _ => c,
}));
