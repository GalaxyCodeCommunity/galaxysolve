// .NET version: 6.0

int[] arr = { 1, 2, 3, 4, 5 };
Console.WriteLine(string.Join(' ', arr));
Console.WriteLine(string.Join(' ', Swap(arr)));

IEnumerable<T> Swap<T>(IEnumerable<T> e)
{
    var en = e.GetEnumerator();
    while (en.MoveNext())
    {
        T f = en.Current;
        if (!en.MoveNext())
        {
            yield return f;
            yield break;
        }
        T s = en.Current;
        yield return s;
        yield return f;

    }
}
