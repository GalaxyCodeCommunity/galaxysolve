// .NET version: 6.0

int[] arr = new int[] { 1, 3, 50, 10 };
Console.WriteLine(EnumerableToString(arr));
Console.WriteLine(EnumerableToString(FilterPrimes(arr)));

static IEnumerable<int> FilterPrimes(IEnumerable<int> e) => e.Where(IsPrime);

static bool IsPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if ((n & 1) == 0 || n < 2 || n % 3 == 0)
        return false;

    int lim = (int)Math.Sqrt(n);

    for (int i = 6; i < lim; i += 6)
    {
        if (n % (i - 1) == 0 || n % (i + 1) == 0)
            return false;
    }

    return true;
}

static string EnumerableToString<T>(IEnumerable<T> e) => $"[{string.Join(", ", e)}]";
