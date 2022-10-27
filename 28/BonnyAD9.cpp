// compiled with 'clang++ -g -Wall -std=c++20'

#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix(size_t height, size_t width);
    Matrix(std::initializer_list<std::initializer_list<double>> data);
    Matrix(const Matrix &m);
    
    size_t Height() const;
    size_t Width() const;
    double &At(size_t i, size_t j);
    const double &At(size_t i, size_t j) const;

    Matrix operator*(const Matrix &r) const;
    Matrix operator*(const double &r) const;

    void Print(std::ostream &out) const;
    bool GussianElimination();
    static Matrix Inverse(const Matrix &m);

private:
    size_t _height;
    size_t _width;
    std::vector<double> _data;

    double &_At(size_t i, size_t j);

    void _TransformRow(size_t ti, size_t i, double mt, double m);
};

// with bonus
Matrix Solve(const Matrix &na, const Matrix &a);
// without bonus
Matrix Solve(const Matrix &m);

int main()
{
    Matrix na{
        { 1,  2, -5, },
        { 7, -1,  1, },
        { 2, -3,  7, },
    };

    Matrix a{
        {  2, },
        {  5, },
        { -6, },
    };

    // with bonus
    Solve(na, a).Print(std::cout);

    Matrix m{
        { 1,  2, -5,  2, },
        { 7, -1,  1,  5, },
        { 2, -3,  7, -6, },
    };

    // without bonus
    Solve(m).Print(std::cout);
}

// with bonus
Matrix Solve(const Matrix &na, const Matrix &a)
{
    auto i = Matrix::Inverse(na);
    return i * a;
}

// without bonus
Matrix Solve(const Matrix &m)
{
    Matrix h = m;
    h.GussianElimination();

    Matrix r(h.Height(), 1);
    for (size_t i = 1; i <= r.Height(); ++i)
        r.At(i, 1) = h.At(i, h.Width());

    return r;
}

Matrix::Matrix(size_t height, size_t width) :
    _height(height),
    _width(width),
    _data(width * height)
{ }

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> data) :
    _height(data.size()),
    _width(_height ? data.begin()->size() : 0),
    _data(_width * _height)
{
    auto d = _data.begin();
    for (auto i : data)
    {
        if (i.size() != _width)
            throw std::invalid_argument("all dimensions must be the same");

        for (auto j : i)
            *d++ = j;
    }
}

Matrix::Matrix(const Matrix &m) :
    _height(m._height),
    _width(m._width),
    _data(m._data)
{ }

size_t Matrix::Height() const { return _height; }
size_t Matrix::Width() const { return _width; }
double &Matrix::At(size_t i, size_t j) { return _At(i - 1, j - 1); }
double &Matrix::_At(size_t i, size_t j) { return _data[i * _width + j]; }

const double &Matrix::At(size_t i, size_t j) const
{
    return _data[(i - 1) * _width + (j - 1)];
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if (_width != m._height)
        return Matrix{ };

    Matrix r(_height, m._width);

    for (size_t i = 1; i <= _height; ++i)
    {
        for (size_t j = 1; j <= m._width; ++j)
        {
            for (size_t ji = 1; ji <= _width; ++ji)
                r.At(i, j) += At(i, ji) * m.At(ji, j);
        }
    }

    return r;
}

Matrix Matrix::operator*(const double &d) const
{
    Matrix r(_height, _width);

    for (size_t i = 1; i <= _height; ++i)
    {
        for (size_t j = 1; j <= _width; ++j)
            r.At(i, j) = At(i, j) * d;
    }

    return r;
}

void Matrix::Print(std::ostream &out) const
{
    out << "(\n";
    for (size_t i = 1; i <= _height; ++i)
    {
        for (size_t j = 1; j <= _width; ++j)
            out << ' ' << At(i, j) << ' ';
        out << '\n';
    }
    out << ')' << std::endl;
}

bool Matrix::GussianElimination()
{
    if (_height > _width)
        return false;

    for (size_t j = 0; j < _height; ++j)
    {
        for (size_t i = 0; i < _height; ++i)
        {
            if (i == j || _At(i, j) == 0)
                continue;

            _TransformRow(i, j, _At(j, j), -_At(i, j));
        }
    }

    bool ret = true;
    for (size_t i = 0; i < _height; ++i)
    {
        if (_At(i, i) == 0)
        {
            ret = false;
            continue;
        }

        for (size_t j = _height; j < _width; ++j)
            _At(i, j) /= _At(i, i);

        _At(i, i) = 1;
    }

    return ret;
}

void Matrix::_TransformRow(size_t ti, size_t i, double mt, double m)
{
    for (size_t j = 0; j < _width; ++j)
        _At(ti, j) = mt * _At(ti, j) + m * _At(i, j);
}

Matrix Matrix::Inverse(const Matrix &m)
{
    if (m._height != m._width)
        return Matrix{ };

    Matrix e(m._height, m._width * 2);

    for (size_t j = 1; j <= m._width; ++j)
    {
        e.At(j, m._width + j) = 1;

        for (size_t i = 1; i <= m._height; ++i)
            e.At(i, j) = m.At(i, j);
    }

    if (!e.GussianElimination())
        return Matrix{ };

    Matrix r(m._height, m._width);

    for (size_t j = 1; j <= r._height; ++j)
    {
        for (size_t i = 1; i <= r._width; ++i)
            r.At(i, j) = e.At(i, j + m._width);
    }

    return r;
}
