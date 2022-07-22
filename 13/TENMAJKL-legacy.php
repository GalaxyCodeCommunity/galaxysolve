<?php

// TODO rewrite 

interface LexerInterface
{
    public function fits(string $char): bool;

    public function ends(): bool;

    public function toToken(): Token;

    public function reset(): self;
}


final class Sequence
{
    private int $pointer = 0;

    public function __construct(
        private array $sequence
    ) {
        
    }

    public function add(LexerInterface $lexer): self
    {
        $this->sequence[] = $lexer;
        return $this;
    }

    /**
     * @return array<LexerInterface>
     */
    public function all(): array
    {
        return $this->sequence;
    }

    public function next(): self
    {
        $this->pointer++;
        return $this;
    }

    public function onNext(): LexerInterface
    {
        return $this->sequence[$this->pointer + 1];
    }


    public function current(): LexerInterface
    {
        return $this->sequence[$this->pointer];
    }

    public function ends(): bool
    {
        return $this->pointer === count($this->sequence) && $this->sequence[$this->pointer - 1]->ends();
    }

    public function resetCurrent(): self
    {
        $this->sequence[$this->pointer] = $this->sequence[$this->pointer]->reset();
        return $this;
    }

    public function reset(): self
    {
        return new self($this->sequence);
    }
}

final class StringLexer implements LexerInterface
{
    private int $position = -1;

    public function __construct(
        public readonly string $string,
        public readonly bool $ignore,
    ) {
        
    }

    public function fits(string $char): bool
    {
        $this->position++;
        return $this->string[$this->position] === $char;
    }

    public function ends(): bool
    {
        return $this->position === strlen($this->string) - 1;
    }

    public function toToken(): Token
    {
        return new Token(TokenKind::String, $this->string);
    }

    public function reset(): self
    {
        return new self($this->string, $this->ignore); 
    }
}

final class CharactersLexer implements LexerInterface
{
    private int $position = -1;

    private string $result = '';

    public function __construct(
        public readonly array $chars,
        public readonly int $lenght,
        public readonly bool $ignore,
    ) {
        
    }  

    public function fits(string $char): bool
    {
        $this->position++;
        $this->result .= $char;
        return in_array($char, $this->chars);
    }

    public function ends(): bool
    {
        return $this->position === $this->lenght - 1;
    }

    public function toToken(): Token
    {
        return new Token(TokenKind::Characters, $this->result);
    }

    public function reset(): self
    {
        return new self($this->chars, $this->lenght, $this->ignore);
    }
}

final class OrLexer implements LexerInterface
{
    /**
     * @var array<LexerInterface>
     */
    private array $sequence;

    private array $backup;

    public function __construct(
        Sequence $sequence,
        public readonly bool $ignore,
    ) {
        $this->sequence = $sequence->all();   
        $this->backup = $this->sequence;
    }

    public function fits(string $char): bool
    {
        foreach ($this->sequence as $index => $item) {
            if (!$item->fits($char)) { 
                unset($this->sequence[$index]);
            }
        }

        return !empty($this->sequence);
    }

    public function ends(): bool
    {
        foreach ($this->sequence as $item) {
            if (!$item->ends()) {
                return false;
            }
        }               

        return true;
    }

    public function toToken(): Token
    {
        return array_values($this->sequence)[0]->toToken();
    }

    public function reset(): self
    {
        $this->sequence = $this->backup;
        return new self((new Sequence($this->sequence))->resetCurrent(), $this->ignore);
    }
}

final class GroupLexer implements LexerInterface
{

    private bool $first = true;

    public function __construct(private Sequence $sequence) 
    {
    }

    public function fits(string $char): bool
    {
        if ($this->first) {
            $this->sequence = $this->sequence->reset();
            $this->sequence->resetCurrent();
            $this->first = false;
        }

        if ($this->sequence->current()->fits($char)) {
            if ($this->sequence->current()->ends()) {
                $this->sequence->next();
                $this->sequence->resetCurrent();
            }
            return true;
        }
        
        return false;
    }

    public function ends(): bool
    {
        return $this->sequence->ends();
    }

    public function toToken(): Token
    {
        $result = []; 
        foreach ($this->sequence->all() as $member) {
            $result[] = $member->toToken();
        }

        return new Token(TokenKind::Group, $result);
    }

    public function reset(): self
    {
        return new self($this->sequence);
    }
}


enum TokenKind
{
    case String;
    case Characters;
    case Group;
}

final class Token
{
    public function __construct(
        public readonly TokenKind $kind,
        public readonly string|array $content
    ) {
        
    }
}

final class LexerException extends Exception
{

}

final class Lexer
{
    public readonly Sequence $sequence;

    private self $master;

    private function __construct(self $master = null)
    {
        $this->master = $master ?? $this;
        $this->sequence = new Sequence([]);
    }

    public function string(string $target, bool $ignore = false): self
    {
        $this->sequence->add(new StringLexer($target, $ignore));
        return $this;
    }

    public function character(array $chars, int $length = 1, bool $ignore = false): self
    {
        $this->sequence->add(new CharactersLexer($chars, $length, $ignore));
        return $this;
    }

    public function or(callable $paterns, bool $ignore = false): self
    {
        $sequence = new self($this->master);
        $sequence = $paterns($sequence);
        $this->sequence->add(new OrLexer($sequence->sequence, $ignore));
        return $this;
    }

    public function self(): self
    {
        $this->sequence->add(new GroupLexer($this->master->sequence));
        return $this;
    }

    public function lex(string $text): array
    {
        $tokens = [];
        foreach (str_split($text) as $position => $char) {
            if ($this->sequence->current()->fits($char)) {
                if ($this->sequence->current()->ends()) {
                    echo $char;
                    if (!$this->sequence->current()->ignore) {
                        $tokens[] = $this->sequence->current()->toToken();
                    }
                    $this->sequence->next();
                }
            } else {
                throw new LexerException('Unexpected character '.$char.' at position '.$position);
            }
        }

        return $tokens;
    }

    public static function make(): self
    {
        return new self();
    }
}


print_r(Lexer::make()
    ->string('(', true)
    ->character(['a', 'b', 'c', 'd'], 3)
    ->or(fn(Lexer $lexer) => 
        $lexer
            ->self()
            ->character(['a', 'b', 'c', 'd'], 3)
    )
    ->string(')', true)
   ->lex('(aaa(bbbccc))'));

