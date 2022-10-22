// .NET version: 6.0

using System.Numerics;

Console.WriteLine(GetAngle(new[] { 4.0, 2 }, new[] { -1.0, 4 }));
Console.WriteLine(Rotate(new(-1, 4), MathF.PI / 2));

static double GetAngle(IEnumerable<double> vec1, IEnumerable<double> vec2)
{
    double dot = 0;
    double l1 = 0;
    double l2 = 0;

    foreach ((var a, var b) in vec1.Zip(vec2))
    {
        dot += a * b;
        l1 += a * a;
        l2 += b * b;
    }

    return Math.Acos(Math.Abs(dot) / (Math.Sqrt(l1) * Math.Sqrt(l2)));
}

static Vector2 Rotate(Vector2 vec, float angle) => new(
    MathF.Cos(angle) * vec.X - MathF.Sin(angle) * vec.Y,
    MathF.Sin(angle) * vec.X + MathF.Cos(angle) * vec.Y
);
