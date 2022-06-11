// .NET version: 6.0

FizzBuzz(Console.Out, 16);

static void FizzBuzz(TextWriter @out, int num)
{
    for (int i = 1; i < num; i++)
    {
        @out.Write($"{i} ");

        if (i % 3 == 0)
            @out.Write("fizz");
        if (i % 5 == 0)
            @out.Write("buzz");

        @out.WriteLine();
    }
}
