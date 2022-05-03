<?php
/**
 * Automaticaly tests files in most common languages (php, haskell, javascript, typescript, java)
 * @author TENMAJKL
 * @license MIT
 */

declare(strict_types=1);

const LANGUAGES = [
    'php' => 'php %file < %data',
    'hs' => 'ghc %file; ./%challenge/%name < %data',
    'js' => 'node %file < %data',
//    'ts' => '', TODO
    'java' => 'javac %file; java %challenge/%name.class',
];

function test(string $file, string $challenge, string $name, string $language): bool
{
    if (!array_key_exists($language, LANGUAGES)) {
        return true;
    }

    $sample = $challenge.'/sample.txt';
    $result = $challenge.'/solution.txt';
    if (!is_file($sample) || !is_file($result)) {
        return true;
    }

    $command = str_replace([
        '%file', 
        '%data', 
        '%name',
        '%challenge'
    ], [
        $file,
        $sample,
        $name,
        $challenge
    ], LANGUAGES[$language]);

    exec($command, $output);
    $expected = file_get_contents($result);
    
    return $expected === implode(PHP_EOL, $output).PHP_EOL;
}

function main($arguments): int
{
    if (count($arguments) < 1) {
        echo 'No arguments provided';
        return -1;
    }

    foreach ($arguments as $file) {
        if (preg_match('/^(\d+)\/(.+?)\.(\w+)$/', $file, $matches)) {
            if (!test(...$matches)) {
                return -1;
            }
        }
    }

    return 0;
}


exit(main(array_slice($argv, 1)));
