// .NET version: 6.0

var arr = new[] { 5, 1, -3, 9, 6, 5, 0 };

BubbleSort(arr, a => a);
Console.WriteLine(string.Join(", ", arr));

// Time complexity: O(n^2)
// Space complexity: O(1)
static void BubbleSort<T>(T[] arr, Func<T, IComparable> cmp)
{
    int endi = arr.Length;
    for (int i = 0; i < arr.Length; i++)
    {
        int newEndi = arr.Length - i;
        for (int j = 1; j < endi; j++)
        {
            if (cmp(arr[j - 1]).CompareTo(cmp(arr[j])) > 0)
            {
                (arr[j - 1], arr[j]) = (arr[j], arr[j - 1]);
                newEndi = j;
            }
        }
        endi = newEndi;
    }
}
