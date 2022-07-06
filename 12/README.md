# Překladový systém se skloňováním:

- Programatický překlad slov (ne vět)
- Můžu si zvolit jazyk, do jakého chci slovo přeložit
- Pokud jazyk neexistuje, tak vypíšu původní slovo
- Původní slova, pomocí kterých vyhledávám slova v jiných jazycích, jsou v angličtině
- Můžu specifikovat počet, podle kterého se slova skloňují (1 člověk, 2 lidi, 10 lidí)
- Pokud počet nespecifikuji, tak je počet 1

// Použití
```ts
translate("dog", "cs"); // pes
translate("cat", "cs", 2); // kočky
translate("human", "en", 10) // humans

// Input
[
    ["dog", "cs"],
    ["cat", "cs", 2],
    ["human", "en", 10]
]

// Output
["pes", "kočky", "humans"]
```

pozn. databázi/strukturu slov pro překlad si musíte vytvořit vy a to pro z inputu, tzv. dog, cat, human.