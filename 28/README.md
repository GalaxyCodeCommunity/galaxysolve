# Řešení soustavy lineárních rovnic
Úkolem je vyřešit soustavu `n` lineárních rovnic o `n` neznámých. Je zakázáno používat funkce z knihovny jazyka pro řešení soustavy lineárních rovnic, pro výpočet invarzní matice a pro výpočet doplňkové matice.

Například (`n`=3):

$x+2y-5z=2$<br>
$7x-y+z=5$<br>
$2x-3y+7z=-6$

```shell
> solve([[1, 2, -5, 2], [7, -1, 1, 5], [2, -3, 7, -6]])
[-5, -69, -29]
```
$x=-5, y=-69, z=-29$

## Bonus
Vyřešte tuto úlohu pomocí inverzní matice. Inverzní matice $A^{-1}$ k matici $A$ je taková matice kterou, když vynásobíme $A$ tak je výsledkem jednotková matice $I$.

$A \times A^{-1}=A^{-1} \times A=I$
