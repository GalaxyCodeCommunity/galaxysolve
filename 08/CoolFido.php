<?php

function fmap($x, $a, $b, $c, $d)
{
	// Nejprve hodnotu $x i konec intervalu $b snížíme o $a a určíme jejich poměr
    $ratio = ($x - $a) / ($b - $a);
    // Tímto poměrem vynásobíme konec cílového intervalu $d snížený o začátek $c a k tomuto výsledku přidáme začátek $c
    return ($d - $c) * $ratio + $c;
}
