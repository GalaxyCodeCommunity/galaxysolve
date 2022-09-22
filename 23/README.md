# Cesarova šifra

Nějaký text (např. `ahoj`) se v cesarove šifře šifruje tak, že se každé jeho písmeno posune o `n` písmen v abecedě.
Pokud by jsme `n` zvolili například `1` tak se `a` změní na  `b`, `h` na `i`, ... a vyjde `bipk`.
Pokud je písmeno na kraji abecedy tak přeteče zpátky na druhý konec například pokud by `n` bylo 2 tak `z` by se změnilo na `b`.
Pokud je `n` záporné tak se písmena posouvají na druhou stranu.

Znaky co nepatří do abecedy (např. `.`) se nezmění. Háčky a čárky nemusí fungovat.

Úkolem bude vytvořit funkci který dokáže šifrovat/dešifrovat cesarovu šifru.

```shell
> cesar("ahoj", 1);
"bipk"
> cesar("bipk", -1);
"ahoj"
> cesar("Hello World!", 10);
"Rovvy Gybvn!"
```

## Bonus
Udělej funkci která rozšifruje cesarovu šifru (alespoň v češtině) ikdyž nezná posun.

```shell
> bonusCZ("Ctypzn sdhipitrct sadjwn itmi.");
"Nejaky dostatecne dlouhy text."
```
