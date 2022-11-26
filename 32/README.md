# Otočení pole
Úkolem je n-krát otočit dvourozměrné pole po směru hodinových ručiček.

```shell
> rotate([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]], 1)
[[7, 4, 1],
 [8, 5, 2],
 [9, 6, 3]]
```
Pole nemusí být čtveraté. Je zakázáno používat funkci z knihovny jazyka
na otočení pole.

## Bonus
Dvourozměrné pole bude předáváno jako jednorozměrné pole o velikosti `s`
a dva parametry `w` a `h` specifikující velikost pole. Pole otočte na místě
(nevytvoříte nové pole ale upravíte hodnoty v daném poli) a vrátíte nové
rozměry pole.

```shell
> rotate([
    1, 2,
    3, 4,
    5, 6], 2, 3, 1)
([5, 3, 1, 
  6, 4, 2], 3, 2)
```

Pokud jazyk nepodporuje mutaci tak tento bonus nejde udělat.
