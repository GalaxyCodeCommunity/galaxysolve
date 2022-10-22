// .NET version: 6.0

Console.WriteLine(Lower((15, 3)));
Console.WriteLine(Optimize((31415926535, 10000000000), 3));

static (long Top, long Bot) Lower((long Top, long Bot) frac)
{
    if (frac.Bot == 0)
        return frac;

    long t = Math.Abs(frac.Top);
    long b = Math.Abs(frac.Bot);

    do (t, b) = (b, t % b);
    while (b != 0);

    return (frac.Top / t, frac.Bot / t);
}

static (long Top, long Bot) Optimize((long Top, long Bot) frac, int dig)
{
    long t = Math.Abs(frac.Top);
    long b = Math.Abs(frac.Bot);

    if (dig < 1 || b == 0 || ((int)Math.Log10(t) + 1 <= dig && (int)Math.Log10(b) + 1 <= dig))
        return frac;
    
    if ((int)Math.Log10(t / b) + 1 > dig)
        return ((long)Math.Pow(10, dig) - 1, 1);

    List<long> infs = new();

    do
    {
        infs.Add(t / b);
        (t, b) = (b, t % b);
    } while (b != 0);

    int i = infs.Count;
    do
    {
        i--;
        t = 0;
        b = 1;

        for (int j = i; j >= 0; j--)
        {
            // if the fraction t/b would be f than the following code does:
            // f=1/(infs[j]+f)
            t += infs[j] * b;
            (t, b) = (b, t);
        }
    } while ((int)Math.Log10(t) + 1 > dig || (int)Math.Log10(b) + 1 > dig);

    return (b, t);
}
