# Řešení polynomu
Úkolem je najít alespoň jedno reálný kořen polynomické rovnice. Polynomická rovnice n-tého stupně je $a_nx^n+b_{n-1}x^{n-1}+...+a_1x+a_0=0$.
Do funkce může být polynom předán jako pole koeficientů ( $a_n, a_{n-1}, ..., a_1, a_0$ ). Řešení musí být přesné alespoň na 3 desetiná místa.
Z knihovny jazyka je zakázáno použít funkce pro hledání kkořenů funkci a pro derivaci.

$x^3+2x^2-5x-1=0$
```shell
> solve([1, 2, -5, -1])
1.5758
```

## Bonus
Najděte všechna reálná řešení polynomické rovnice. Polynomická rovnice n-tého stupně může mít až n řešení.

```shell
> solve([1, 2, -5, -1])
[-3.3885, -0.18728, 1.5758]
```

## Bonus 2
Najděte alespoň jeden kořen libovolné spojité funkce.

```shell
> solve(x => x * pow(E, sin(x)) - 2)
3.85865138368111
```
