// .NET version: 7.0

using System.Numerics;

namespace GS31;

class Program
{
    static void Main(string[] args)
    {
        var a = new[] { 1.0, 2, 3 };
        var b = new[] { 2.0, 4, 6 };

        // No bonus
        Console.WriteLine(string.Join(' ', Convolve<double>(a, b)));
    }

    // No bonus
    static T[] Convolve<T>(ReadOnlySpan<T> a, ReadOnlySpan<T> b) where T : IAdditionOperators<T, T, T>, IMultiplyOperators<T, T, T>, IAdditiveIdentity<T, T>
    {
        var res = new T[a.Length + b.Length - 1];
        var c = res.AsSpan();
        c.Fill(T.AdditiveIdentity);

        for (int i = 0; i < a.Length; i++)
        {
            for (int j = 0; j < b.Length; j++)
                c[i + j] += a[i] * b[j];
        }

        return res;
    }
}
