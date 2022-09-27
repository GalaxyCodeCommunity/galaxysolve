// .NET version: 6.0

int[] arr = Enumerable.Range(0, 10).ToArray();

Console.WriteLine(string.Join(' ', arr));
Shuffle(arr.AsSpan());
Console.WriteLine(string.Join(' ', arr));

void Shuffle<T>(Span<T> span)
{ 
    for (; span.Length > 1; span = span[1..])
    {
        int r = Random.Shared.Next(span.Length);
        (span[0], span[r]) = (span[r], span[0]);
    }
}
