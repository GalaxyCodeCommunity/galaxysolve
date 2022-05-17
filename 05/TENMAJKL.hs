range :: Int -> Int -> [Int]
range from to 
    | to == from = [from]
    | from < to = range from (to - 1) ++ [to]
    | otherwise = range from (to + 1) ++ [to]

main = do
    print (range 5 1)
    print (range 1 5)
