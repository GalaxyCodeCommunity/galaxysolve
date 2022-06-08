<?php

// TODO

function fmap(float $x, float $a, float $b, float $c, float $d): float
{
    $shift = $a - $c;
    $b_shifted = $b - $shift;
    $mult = $d / $b_shifted;
    return ($x - $shift) * $mult;
}

