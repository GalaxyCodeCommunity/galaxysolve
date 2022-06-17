main = do
    print $ primes [1, 3, 50, 10]

primes :: Integral a => [a] -> [a]
primes = filter (\x -> isPrime 6 x)

isPrime :: Integral a => a -> a -> Bool
isPrime _ 2 = True
isPrime _ 3 = True
isPrime p n
    | n < 2 || n `mod` 2 == 0 || n `mod` 3 == 0 || n `mod` (p - 1) == 0 || n `mod` (p + 1) == 0 = False
    | p > (floor.sqrt.fromIntegral) n = True
    | otherwise = isPrime (p + 6) n