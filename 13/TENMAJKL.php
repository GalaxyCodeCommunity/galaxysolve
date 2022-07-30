<?php

final class Parser
{
    const Number = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
    const Letter = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'];

    private array $parser = [];

    private bool $or = false;

    public static function make(): self
    {
        return new self();
    }

    public function string(string $target, bool $ignore = false): self
    {
        return $this->determin(['string', [$target, $ignore]]);
    }

    public function sequence(array $chars, int $min = 1, int $max = 2560, bool $ignore = false): self
    {
        return $this->determin(['sequence', [$chars, $min, $max, $ignore]]);
    }

    public function or(): self
    {
        $this->or = true;
        return $this;
    }

    public function self(): self
    {
        $this->determin(['self']);
        return $this;
    }

    public function parse(string $target): array
    {
        $result = [];
        foreach ($this->parser as $token) {
            $parsed = $this->call($token, $target);
            if ($parsed instanceof Exception) {
                throw $parsed;
            }
            if ($parsed[0]) {
                $result[] = $parsed[0];
            }
            $target = $parsed[1];
        }

        return $target 
            ? [$result, $target] 
            : $result
        ;
    }

    private function determin(array $fn): self
    {
        if ($this->or) {
            $this->parser[array_key_last($this->parser)] = ['or', [$this->parser[array_key_last($this->parser)], $fn]] ;
            $this->or = false;
         }  else {
             $this->parser[] = $fn;
         }

         return $this;
    }

    private function parseString(string $target, string $token, bool $ignore): Exception|array
    {
        if (!str_starts_with($target, $token)) {
            return new Exception('Expected '.$token);
        }

        return [
            $ignore ? null : $token,
            substr($target, strlen($token)),
            0,
        ];
    }

    private function parseSequence(string $target, array $chars, int $min, int $max, bool $ignore): Exception|array
    {
        $index = 0;
        $result = '';
        while (in_array($curent = ($target[$index] ?? null), $chars)) {
            if ($index > $max) {
                break;
            }

            $result .= $curent;

            $index++;
        }

        if ($index < $min) {
            return new Exception('Unexpected '.$curent);
        }

        return [
            $ignore ? null : $result,
            substr($target, strlen($result)),
            $index,
        ];
    }

    private function parseOr(string $target, array $first, array $second): Exception|array
    {
        if (is_array($result = $this->call($first, $target))) {
            return $result;
        }

        return $this->call($second, $target);        
    }

    private function call(array $token, string $target): Exception|array
    {
        if ($token[0] === 'self') {
            return $this->parse($target);
        }
        return $this->{'parse'.ucfirst($token[0])}($target, ...$token[1]);       
    }
}

print_r(Parser::make()
    ->string('(')
    ->sequence(Parser::Letter)
    ->sequence([' '], ignore: true)
    ->sequence(Parser::Letter)
    ->or()
    ->self()
    ->sequence([' '], ignore: true)
    ->sequence(Parser::Letter)
    ->or()
    ->self()
    ->string(')')
    ->parse('(plus parek (minus rizek parek))'))
;
