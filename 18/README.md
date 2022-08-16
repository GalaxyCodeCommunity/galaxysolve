# Url parser

Dnesnim ukolem bude vytvorit url parser, ktery rodeli url na

- protokol 
- host 
- port
- uri
- query

Pochopitelne bez pouziti dedikovane funkce. Vystup muze byt struktura/objekt/asociativni pole/...

```php
parse("https://localhost:8000/foo/baz?bar=baz");
[
    "protocol" => "https",
    "host" => "localhost",
    "port" => "8000",
    "uri" => "foo/baz",
    "query" => "bar=baz"
]
```
