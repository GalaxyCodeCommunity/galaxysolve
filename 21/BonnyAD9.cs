// .NET version: 6.0

Rng rng = new();
for (int i = 0; i < 100; i++)
    Console.WriteLine(rng.NextUint() % 100);
class Rng
{
    protected ulong Cur { get; set; }

    public Rng(ulong seed) => Cur = seed;
    public Rng() : this(unchecked((ulong)DateTime.Now.Ticks)) { }

    public uint NextUint()
    {
        Cur ^= Cur << 19;
        Cur ^= Cur << 20;
        Cur ^= Cur >> 9;
        return (uint)(Cur >> 32) + (uint)(Cur & uint.MaxValue);
    }
}
