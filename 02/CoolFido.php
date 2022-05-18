<?php

function reverse(array $array)
{
	$out = [];

	for ($i = count($array) - 1; $i >= 0; $i--)
		$out[] = $array[$i];

	return $out;
}

echo implode(', ', reverse([1, 2, 3]));
