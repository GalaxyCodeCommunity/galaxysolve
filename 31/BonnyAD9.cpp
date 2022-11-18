#include <iostream>
#include <vector>

std::vector<double> Convolve(const std::vector<double> &a, const std::vector<double> &b);
template <typename Iterator> void Print(Iterator begin, Iterator end);

int main()
{
    std::vector<double> a{ 1, 2, 3 };
    std::vector<double> b{ 2, 4 ,6 };

    // no bonus
    auto res = Convolve(a, b);
    Print(res.begin(), res.end());
}

// no bonus
std::vector<double> Convolve(const std::vector<double> &a, const std::vector<double> &b)
{
    std::vector<double> res(a.size() + b.size() - 1, 0);

    for (size_t i = 0; i < a.size(); ++i)
    {
        for (size_t j = 0; j < b.size(); ++j)
            res[i + j] += a[i] * b[j];
    }
    return res;
}

template <typename Iterator> void Print(Iterator begin, Iterator end)
{
    while (begin != end)
        std::cout << *begin++ << ' ';
    std::cout << std::endl;
}
