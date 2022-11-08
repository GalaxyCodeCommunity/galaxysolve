// .NET version: 7.0

using System.Numerics; // IComparisonOperators

internal static class Program
{
    private static void Main(string[] args)
    {
        ReadOnlySpan<int> s = stackalloc[] { -5, 2, 0, 5, 9, 26 };

        // with bonus
        // Time complexity: O(log N)
        Console.WriteLine(s.MyBinarySearch(5));
    }

    // the offset is there because of TCO
    static int MyBinarySearch<T>(this ReadOnlySpan<T> arr, T item, int offset = 0) where T : IComparisonOperators<T, T, bool>
    {
        if (arr.Length == 0)
            return -1;
        
        int p = arr.Length / 2;
        if (arr[p] == item)
            return p + offset;

        return arr[p] > item
            ? arr[..p].MyBinarySearch(item, offset)
            : arr[(p + 1)..].MyBinarySearch(item, offset + p + 1);
    }
}
