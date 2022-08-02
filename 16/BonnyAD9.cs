// .NET version: 6.0

Console.WriteLine(DigitCount(37));

static int DigitCount(int num) => num == 0 ? 1 : (int)Math.Log10(Math.Abs(num)) + 1;
