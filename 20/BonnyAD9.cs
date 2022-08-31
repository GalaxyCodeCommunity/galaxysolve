// .NET version: 6.0

Console.WriteLine(string.Join(' ', Decompose(12))); // 2 2 3

IEnumerable<int> Decompose(int num)
{
    for (int i = 2; num > 1; i++)
    {
        while (num % i == 0)
        {
            yield return i;
            num /= i;
        }
    }
}
