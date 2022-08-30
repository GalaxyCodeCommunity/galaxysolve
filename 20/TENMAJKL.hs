firstThat :: [a] -> (a -> Bool) -> a
firstThat target f
    | f(head target) = head target
    | otherwise = firstThat(tail target) f

findDivider :: Int -> Int
findDivider number = firstThat [2..number] (\item -> number `mod` item == 0)

decompose :: Int -> [Int]
decompose number
    | divider == number = [number]
    | otherwise = decompose divider ++ decompose (number `div` divider) 
    where divider = findDivider number

main = print (decompose 12)
