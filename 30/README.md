# Hledání v poli

Úkolem je která najde na jakém indexu se nachází hledaný prvek v seřazeném poli. Pokud funkce prvek nenajde, tak vrátí nevalidní hodnotu (-1 nebo maximální hodnotu daného typu).
Je zakázáno používat funkce z knihovny jazyka na hledání.

```shell
> find(5, [-5, 2, 0, 5, 9, 26])
3
> find(10, [-5, 2, 0, 5, 9, 26])
-1
```

## Bonus
Funkce bude mít menšní než lineární složitost.
