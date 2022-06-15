// .NET version: 6.0

Console.Write("cislo: ");
FizzBuzz(Console.Out, int.Parse(Console.ReadLine()!));

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
