// compiled with 'clang++ -g -Wall -std=c++20'

#include <iostream>
#include <array>

template <typename RandomAccessIterator, typename T>
size_t BinarySearch(
    const RandomAccessIterator begin,
    const RandomAccessIterator end,
    const T item
);

int main()
{
    std::array arr{ -5, 2, 0, 5, 9, 26 };

    // with bonus
    // Time complexity: O(log N)
    std::cout << BinarySearch(arr.begin(), arr.end(), 26) << std::endl;
}

// the offset (and wrapper) is here because of TCO
template <typename RandomAccessIterator, typename T>
size_t _BinarySearch(
    const RandomAccessIterator begin,
    const RandomAccessIterator end,
    const T item,
    const size_t offset
)
{
    const size_t len = end - begin;

    if (len == 0)
        return SIZE_MAX;

    const size_t p = len / 2;
    if (begin[p] == item)
        return offset + p;

    return begin[p] > item
        ? _BinarySearch(begin, begin + p, item, 0)
        : _BinarySearch(begin + p + 1, end, item, offset + p + 1);
}

template <typename RandomAccessIterator, typename T>
size_t BinarySearch(
    const RandomAccessIterator begin,
    const RandomAccessIterator end,
    const T item
) { return _BinarySearch(begin, end, item, 0); }
