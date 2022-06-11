// .NET version: 6.0

Console.WriteLine($"5:   0..10  == {FMap(5, 0, 10, 0, 100),4}: 0..100");
Console.WriteLine($"65: 50..100 == {FMap(65, 50, 100, 0, 255),4}: 0..255");

static double FMap(double x, double a, double b, double c, double d) => (x - a) * (d - c) / (b - a) + c;
