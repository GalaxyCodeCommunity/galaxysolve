<?php

declare(strict_types=1);

// HAHAHAHAHA BOGOSORT IS THE WAY HAHAHAHAHA
// this algorithm sorts depending on your time so it actualy matters when you run it lol
// oh we were supposed to get under O(n log n)
// but technicaly you can get O(1) here lol

function bogo_sort(array $array): array
{
    while (!is_sorted($array)) {
        shuffle($array);
    }

    return $array;
}

function is_sorted(array $array): bool
{
    $count = count($array) - 1;
    for ($index = 0; $index < $count; $index++) {
        if ($array[$index] > $array[$index + 1]) {
            return false;
        }
    }

    return true;
}

//print_r(bogo_sort([7, 1, 0, 8, 5, 3, 6, 4, 9, 10, 2]));

// Ok now lets get under n log n

function counting(array $array): array
{
    $container = [];
    foreach ($array as $item) {
        $container[$item] = isset($container[$item]) 
            ? $container[$item] + 1
            : 1
        ;
    }

    print_r($container);

    $result = [];
    foreach ($container as $number => $item) {
        for ($index = 0; $index < $item; $index++) {
            $result[] = $number;
        }
    }

    return $result;
}

print_r(counting([7, 1, 0, 8, 5, 3, 6, 4, 9, 10, 2]));
