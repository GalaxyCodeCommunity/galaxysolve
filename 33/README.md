# Yamiterova pipe

Vasim ukolem bude vygenerovat function overloading pro pipovy system od @yamiteru tj: 

Tj vygenervoat toto:

```
export function pipe<A, B>(
  ab: PipeFn<A, B>,
): PipeReturn<A, B>;
export function pipe<A, B, C>(
  ab: PipeFn<A, B>,
  bc: PipeFn<B, C>
): PipeReturn<A, C>;
...etc
```
