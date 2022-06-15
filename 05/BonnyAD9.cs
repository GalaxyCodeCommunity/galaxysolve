// .NET version: 6.0

Console.Write("range: ");
string[] nums = Console.ReadLine()!.Split(' ');
Console.WriteLine(string.Join(' ', Range(int.Parse(nums[0]), int.Parse(nums[1]))));

static IEnumerable<int> Range(int start, int end)
{
    if (start == end)
    {
        yield return start;
        yield break;
    }

    int step = end - start;
    step /= Math.Abs(step);
    (int s, int l) = start > end ? (end, start) : (start, end);

    for (int i = start; i >= s && i <= l; i += step)
        yield return i;
}
