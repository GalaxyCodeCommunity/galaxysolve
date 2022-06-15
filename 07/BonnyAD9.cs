// .NET version: 6.0

Console.Write("string: ");
Console.WriteLine(BCount(Console.ReadLine()!));

static int BCount(string s) => s.Aggregate<char, (int b, int n)>((0, 0), (t, c) => c switch
{
    '(' => (t.b, t.n + 1),
    ')' => t.n <= 0 ? t : (t.b + 1, t.n - 1),
    _ => t,
}).b;
