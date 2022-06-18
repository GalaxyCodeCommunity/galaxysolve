main = do
    print $ range 1 5
    print $ range 5 1

range :: Integral a => a -> a -> [a]
range a b
    | a == b = [a]
    | a < b = a : range (a + 1) b
    | otherwise = a : range (a - 1) b