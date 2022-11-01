// .NET version: 6.0

using System.Text;

Matrix na = new(new double[,]
{
    { 1,  2, -5, },
    { 7, -1, 1, },
    { 2, -3, 7, },
});

Matrix a = new(new double[,]
{
    {  2, },
    {  5, },
    { -6, },
});

Console.WriteLine(Solve(na, a));


// bonus
Matrix? Solve(Matrix na, Matrix a)
{
    Matrix? i = Matrix.Inverse(na);
    if (i is null)
        return null;

    return i * a;
}

class Matrix
{
    private readonly double[] _data = Array.Empty<double>();
    public int Height { get; init; }
    public int Width { get; init; }

    public double this[int i, int j]
    {
        get => At(i - 1, j - 1);
        set => At(i - 1, j - 1) = value;
    }

    ref double At(int i, int j) => ref _data[i * Width + j];

    public Matrix(int height, int width)
    {
        _data = new double[width * height];
        Height = height;
        Width = width;
    }

    public Matrix(double[,] values)
    {
        _data = new double[values.Length];
        Height = values.GetLength(0);
        Width = values.GetLength(1);

        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
                At(i, j) = values[i, j];
        }
    }

    public bool GaussianElimination()
    {
        if (Width < Height)
            return false;

        for (int j = 0; j < Height; j++)
        {
            for (int i = 0; i < Height; i++)
            {
                if (i == j)
                    continue;

                LinearCombination(i, j, At(j, j), -At(i, j));
            }
        }

        for (int i = 0; i < Height; i++)
        {
            double d = At(i, i);
            for (int j = Height; j < Width; j++)
                At(i, j) /= d;
            At(i, i) = 1;
        }

        return true;
    }

    private void LinearCombination(int mi, int i, double mm, double m)
    {
        for (int j = 0; j < Width; j++)
            At(mi, j) = At(mi, j) * mm + At(i, j) * m;
    }

    public static Matrix? Inverse(Matrix m)
    {
        if (m.Width != m.Height)
            return null;

        Matrix h = new(m.Height, m.Width * 2);

        for (int i = 0; i < m.Height; i++)
        {
            for (int j = 0; j < m.Width; j++)
                h.At(i, j) = m.At(i, j);

            h.At(i, m.Width + i) = 1;
        }

        h.GaussianElimination();

        Matrix r = new(m.Height, m.Width);

        for (int i = 0; i < r.Height; i++)
        {
            for (int j = 0; j < r.Width; j++)
                r.At(i, j) = h.At(i, j + m.Width);
        }

        return r;
    }

    public static Matrix operator *(Matrix a, Matrix b)
    {
        if (a.Width != b.Height)
            throw new ArgumentException("Invalid matrix dimensions", nameof(a));

        Matrix r = new(a.Height, b.Width);

        for (int i = 0; i < a.Height; i++)
        {
            for (int j = 0; j < b.Width; j++)
            {
                for (int ji = 0; ji < a.Width; ji++)
                    r.At(i, j) += a.At(i, ji) * b.At(ji, j);
            }
        }

        return r;
    }

    public override string ToString()
    {
        StringBuilder sb = new();

        sb.AppendLine("(");
        for (int i = 0; i < Height; i++)
        {
            sb.Append('(');
            for (int j = 0; j < Width; j++)
                sb.Append(' ').Append(At(i, j)).Append(' ');
            sb.AppendLine(")");
        }
        sb.AppendLine(")");
        return sb.ToString();
    }
}
