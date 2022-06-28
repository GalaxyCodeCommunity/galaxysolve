// .NET version: 6.0

Console.WriteLine(IsLeap(2016));
Console.WriteLine(IsLeap(2017));

static bool IsLeap(int year) => year % 400 == 0 || (((year & 3) == 0) && year % 100 != 0);
