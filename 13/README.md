# Modulární parser

Cílem je vytvořit modulární core, který se dá rozšířit o různé parsery. Takový parser se dá poté použít místo RegExpu, nebo pro parsování programovacího jazyka.

Parser vždy bere string jako input a vrací objekt `{ source: string, index: number } & ({ result: any } | { error: any })`.

Objekt musí být podle potřeby modulární/rozšířitelný. Tzv. všechny příklady dole používají stejný core, ale přesto mají jiný tvar objektu.

## Příklady

### Cena

``` typescript
// input
"2000 Kč"

// output
{
    source: "2000 Kč",
    index: 0,
    result: [
        {
            source: "2000",
            index: 0,
            result: 2000
        },
        {
            source: " ",
            index: 4,
            result: " "
        },
        { 
            source: "Kč",
            index" 5,
            result" "Kč"
        }
    ]
}
```

### Email

``` typescript
// input
"test123@example.com"

// output
{
    result: [
        {
            type: "username",
            result: "test123"
        },
        {
            type: "domain",
            result: "example.com"
        }
    ]
}
```

### LISP

``` typescript
// input
"(* (+ 2 6) (- 6 (/ 4 2)))"

// output
{
    type: "list",
    content: [
        {
            type: "operator",
            content: "*"
        },
        {
            type: "list",
            content: [
                {
                    type: "operator",
                    content: "+"
                },
                {
                    type: "atom",
                    content: 2
                },
                {
                    type: "atom",
                    content: 6
                }
            ]
        },
        {
            type: "list",
            content: [
                {
                    type: "operator",
                    content: "-"
                },
                {
                    type: "atom",
                    content: 6
                },
                {
                    type: "list",
                    content: [
                        {
                            type: "operator",
                            content: "/"
                        },
                        {
                            type: "atom",
                            content: 4
                        },
                        {
                            type: "atom",
                            content: 2
                        }
                    ]
                }
            ]
        }
    ]
```

## Použití

Toto je jen pseudo-kód. API ve skutečnosti nemusí nutně vypadat přesně takhle. Cíl tohoto příkladu použití je jen demonstrace modularity.

``` typescript
const emailParser = map(
    sequence([
        type("username", result(letters)),
        string("@"),
        type("domain", result(letters))
    ]),
    ({ result }) => [result[0], result[2]] 
);
```
