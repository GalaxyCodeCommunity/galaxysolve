<?php

function f($n)
{
	echo 'cislo: ' . $n;
	for($i = 1; $i <= $n; $i++)
		echo PHP_EOL . $i . ($i % 3 && $i % 5 ? '' : ' ') . ($i % 3 == 0 ? 'fizz' : '') . ($i % 5 == 0 ? 'buzz' : '');
}

echo f(15);
