<?php

declare(strict_types=1);

function is_color(string $target): bool
{
    return preg_match('/^#[a-f0-9A-F]{6}$/', $target) === 1;
}

