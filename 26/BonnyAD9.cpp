// compiled with 'clang++ -g -Wall -std=c++20'

#include <iostream>
#include <vector>

bool Lower(int &top, int &bot);
bool Optimize(int &top, int &bot, int dig);

int main()
{
    int top = 314159265;
    int bot = 100000000;
    Lower(top, bot);
    std::cout << top << '/' << bot << std::endl;
    Optimize(top, bot, 3);
    std::cout << top << '/' << bot << std::endl;
}

bool Lower(int &top, int &bot)
{
    if (bot == 0)
        return false;

    int t = abs(top);
    int b = abs(bot);
    int h;

    do
    {
        h = t % b;
        t = b;
        b = h;
    } while (b != 0);

    top /= t;
    bot /= t;

    return true;
}

bool Optimize(int &top, int &bot, int dig)
{
    if (bot == 0)
        return false;

    int t = top / bot;

    if (log10(t) + 1 > dig)
    {
        top = pow(10, dig) - 1;
        bot = 1;
        return true;
    }

    if (log10(top) + 1 <= dig && log10(bot) + 1 <= dig)
        return true;

    t = abs(top);
    int b = abs(bot);
    std::vector<int> infs;
    do
    {
        int h = t % b;
        infs.push_back(t / b);
        t = b;
        b = h;
    } while (b != 0);

    int i = infs.size();
    do
    {
        t = 0;
        b = 1;
        for (int j = --i; j >= 0; --j)
        {
            t += infs[j] * b;
            std::swap(t, b);
        }
        std::swap(t, b);
    } while ((int)log10(t) + 1 > dig || (int)log10(b) + 1 > dig);

    top = t * (top / abs(top));
    bot = b * (bot / abs(bot));
    return true;
}
