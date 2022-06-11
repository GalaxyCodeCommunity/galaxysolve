// .NET version: 6.0

int[] arr = { 1, 2, 3 };

Console.WriteLine(EnumToString(arr));
Reverse(arr.AsSpan());
Console.WriteLine(EnumToString(arr));

void Reverse<T>(Span<T> span)
{
    if (span.Length <= 1)
        return;
    (span[0], span[^1]) = (span[^1], span[0]);
    Reverse(span[1..^1]);
}

string EnumToString<T>(IEnumerable<T> e) => $"[{string.Join(", ", e)}]";
