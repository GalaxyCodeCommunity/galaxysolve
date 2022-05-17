<?php

function f(int $a, int $b)
{
	$out = [];

	for ($i = $a; $i != ($b + ($a < $b ? 1 : -1)); $i += ($a < $b ? 1 : -1))
		$out[] = $i;

	return $out;
}
