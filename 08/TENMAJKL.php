<?php

function fmap(float $x, float $a, float $b, float $c, float $d): float
{
    return ($d - $c) / ($b - $a) * ($x - $a) + $c;
}

foreach ([[0, 127],
[127, 255],
[255, 383],
[383, 511],
[511, 639],
[639, 767],
[767, 895],
[895, 1023]] as [$x, $y]) {
    echo fmap($x, 0, 1023, 767, 1023).PHP_EOL;
}
