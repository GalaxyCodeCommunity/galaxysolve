// .NET version: 6.0

namespace GS29;

class Program
{
    const double smallValue = 0.000001;

    static void Main(string[] args)
    {
        var p = new[] { 1.0, 2, -5, -1 };

        // no bonus
        Console.WriteLine(Newton(p)); // -0.1872837251102239

        // bonus 1
        Console.WriteLine(string.Join(' ', AllNewton(p))); // -0.1872837251102239 1.575773472651936 -3.388489747541712

        // bonus 2
        Console.WriteLine(Newton(x => x * Math.Pow(Math.E, Math.Sin(x)) - 2)); // 0.9088062593639037
    }

    // bonus 2
    static double Newton(Func<double, double> f, double init = 0, double o = smallValue)
    {
        int lim = o == 0 ? (int)(1 / smallValue) : (int)Math.Abs(1 / o);
        for (int i = 0; i < lim; i++)
        {
            double ni = init - f(init) / LazyDerivative(f, init, o);
            if (Math.Abs(init - ni) <= o)
                return ni;
            init = ni;
        }
        return double.NaN;
    }

    static double LazyDerivative(Func<double, double> f, double x, double o = smallValue) => (f(x + o) - f(x)) / o;

    // bonus 1
    static List<double> AllNewton(ReadOnlySpan<double> coef, double init = 0, double o = smallValue)
    {
        // coef copy
        Span<double> cc = stackalloc double[coef.Length];
        coef.CopyTo(cc);
        List<double> roots = new();

        while (cc.Length > 1)
        {
            double r = Newton(cc, o: o);
            if (double.IsNaN(r))
                return roots;
            roots.Add(r);
            cc = HornerRem(cc, r);
        }

        return roots;
    }

    static Span<double> HornerRem(Span<double> coef, double x)
    {
        for (int i = 1; i < coef.Length; i++)
            coef[i] += x * coef[i - 1];
        return coef.Length == 0 ? coef : coef[..^1];
    }

    // no bonus
    static double Newton(ReadOnlySpan<double> coef, double init = 0, double o = smallValue)
    {
        int lim = o == 0 ? (int)(1 / smallValue) : (int)Math.Abs(1 / o);
        for (int i = 0; i < lim; i++)
        {
            double ni = init - Horner(coef, init) / HornerDerivative(coef, init);
            if (Math.Abs(init - ni) <= o)
                return ni;
            init = ni;
        }
        return double.NaN;
    }

    static double HornerDerivative(ReadOnlySpan<double> coef, double x)
    {
        double r = 0;
        for (int i = 0; i < coef.Length - 1; i++)
            r = r * x + coef[i] * (coef.Length - i - 1);
        return r;
    }

    static double Horner(ReadOnlySpan<double> coef, double x)
    {
        double r = 0;
        foreach (var c in coef)
            r = r * x + c;
        return r;
    }
}
