<?php

function fmap(float $x, float $a, float $b, float $c, float $d): float
{
    return ($d - $c) / ($b - $a) * ($x - $a) + $c;
}
