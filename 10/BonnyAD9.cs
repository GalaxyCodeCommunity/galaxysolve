// .NET version: 6.0

int[] arr1 = new[] { 1, 2 };
int[] arr2 = new[] { 3, 4 };

Console.WriteLine(string.Join(' ', Zip(arr1, arr2)));

static IEnumerable<T> Zip<T>(IEnumerable<T> e1, IEnumerable<T> e2)
{
    var en1 = e1.GetEnumerator();
    var en2 = e2.GetEnumerator();

    bool c1;
    bool c2;
    
    while ((c1 = en1.MoveNext()) & (c2 = en2.MoveNext()))
    {
        yield return en1.Current;
        yield return en2.Current;
    }

    if (!c1 && !c2)
        yield break;

    if (c2)
        en1 = en2;

    do yield return en1.Current;
    while (en1.MoveNext());
}
