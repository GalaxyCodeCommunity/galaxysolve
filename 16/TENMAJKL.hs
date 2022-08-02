countDigits :: Int -> Int
countDigits number 
    | number `div` 10 == 0 = 1
    | otherwise = countDigits (number `div` 10) + 1

main = print (countDigits 37)
