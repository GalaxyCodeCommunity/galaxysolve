// .NET version: 6.0

using System.Text.RegularExpressions;

Console.Write("color: ");
Console.WriteLine(IsColor(Console.ReadLine()!));

static bool IsColor(string s) => s.Length == 7 && Regex.IsMatch(s, "#[0-1a-fA-F]{6}");
