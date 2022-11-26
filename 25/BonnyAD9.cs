// .NET version: 6.0

var arr = new[] { 1, 2, 3 };
foreach (var p in Perm(arr))
    Console.WriteLine(string.Join(' ', p));

static IEnumerable<T[]> Perm<T>(IEnumerable<T> values) where T : IComparable
{
    var arr = values.OrderBy(p => p).ToArray();

    do
    {
        yield return arr.ToArray();
    } while (NextPermutation(arr.AsSpan()));

    yield break;
}

static bool NextPermutation<T>(Span<T> arr) where T : IComparable
{
    if (arr.Length < 1)
        return false;

    int p = arr.Length - 2;
    while (p >= 0 && arr[p].CompareTo(arr[p + 1]) >= 0)
        p--;

    if (p < 0)
        return false;

    int ps = arr.Length - 1;
    while (arr[ps].CompareTo(arr[p]) <= 0)
        ps--;

    (arr[ps], arr[p]) = (arr[p], arr[ps]);

    Reverse(arr[(p + 1)..]);
    return true;
}

static void Reverse<T>(Span<T> span)
{
    for (; span.Length >= 2; span = span[1..^1])
        (span[0], span[^1]) = (span[^1], span[0]);
}
