# Konvoluce
Napište funkci která udělá konvoluci dvou vektorů. Konvoluce vektorů je vektor kde každý jeho prvek je součet součinů překrití vstupních vektorů
kde druhý vektor je obrácený. Například pokud $a=(1, 2, 3)$ a $b=(2, 4, 6)$ tak $a \ast b=(2, 8, 20, 24, 18)$ protože:
```
    1 2 3    1 2 3  1 2 3        1 2 3    1 2 3
6 4 2    , 6 4 2  , 6 4 2,         6 4 2,     6 4 2
1×2      , 1×4+2×2, 1×6+2×4+3×2, 2×6+3×4, 3×6
2        , 8      , 20         , 24     , 18
```
(délky vektorů $a$ a $b$ nemusí být stejné). Z knihovny jazyka je zakázáno pužít funkci na konvoluci, násobení polynomů a libovolnou formu DFT
(discrete fourier transform).

```shell
> convolve([1, 2, 3], [2, 4, 6])
[2, 8, 20, 24, 18]
```

## Bonus
Pokuste se to vyřešit v lepší časové složitosti než $O(n^2)$. (toto je docela těžké)
