<?php

// TODO 

interface LexerInterface
{
    public function fits(string $char): bool;

    public function ends(): bool;

    public function toToken(): Token;
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
}

final class StringLexer implements LexerInterface
{
    private int $position = -1;

    public function __construct(
        public readonly string $string
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
}

final class CharactersLexer implements LexerInterface
{
    private int $position = -1;

    private string $result = '';

    public function __construct(
        public readonly array $chars,
        public readonly int $lenght,
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
}

final class GroupLexer implements LexerInterface
{
    public function __construct(
        public readonly Sequence $sequence,
        public readonly int $times
    ) {
        
    }

    public function fits(string $char): bool
    {
        if ($this->sequence->current()->fits($char)) {
            if ($this->sequence->current()->ends()) {
                $this->sequence->next();
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
}

final class OrLexer implements LexerInterface
{
    /**
     * @var array<LexerInterface>
     */
    private array $sequence;

    public function __construct(Sequence $sequence) 
    {
        $this->sequence = $sequence->all();   
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
        $this->sequence = array_values($this->sequence);
        return $this->sequence[0]->toToken();
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

    public function __construct()
    {
        $this->sequence = new Sequence([]);
    }

    public function string(string $target): self
    {
        $this->sequence->add(new StringLexer($target));
        return $this;
    }

    public function character(array $chars, int $length = 1): self
    {
        $this->sequence->add(new CharactersLexer($chars, $length));
        return $this;
    }

    public function or(callable $paterns): self
    {
        $sequence = new self();
        Closure::fromCallable($paterns)->call($sequence);
        $this->sequence->add(new OrLexer($sequence->sequence));
        return $this;
    }

    public function match(callable $patern, int $times = 1): self
    {
        $sequence = new self();
        Closure::fromCallable($patern)->call($sequence);
        $this->sequence->add(new GroupLexer($sequence->sequence, $times));
        return $this;
    }

    public function group(): self
    {
        $this->sequence->add(new GroupLexer($this->sequence, 1));
        return $this;
    }

    public function lex(string $text): array
    {
        $tokens = [];
        foreach (str_split($text) as $position => $char) {
            if ($this->sequence->current()->fits($char)) {
                if ($this->sequence->current()->ends()) {
                    if ($this->sequence->current() instanceof GroupLexer) {
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
        return new self;
    }
}


print_r(Lexer::make()
    ->string('(')
    ->match(function() {
        $this
            ->character(range(0, 9), 2)
            ->string(' ')
            ->group()
            ->string(' ')
        ;
    })
    ->string(')')
    ->lex('(19 25  )'));

