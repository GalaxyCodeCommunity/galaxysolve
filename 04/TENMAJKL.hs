isPrime :: Int -> Bool
isPrime number = length(takeWhile (\item -> number `mod` item /= 0) [2..number `div` 2]) == number `div` 2 - 1 -- TODO sqrt

allPrime :: [Int] -> [Int]
allPrime = filter isPrime

main = print ( allPrime [1, 5, 32, 10, 37, 9, 13, 23] )
