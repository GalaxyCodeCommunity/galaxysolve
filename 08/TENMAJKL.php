<?php

function fmap(int $x, int $a, int $b, int $c, int $d): float
{
    $shift = $a - $c;
    $b_shifted = $b - $shift;
    $mult = $d / $b_shifted;
    return ($x - $shift) * $mult;
}
