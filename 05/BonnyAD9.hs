main = do
    print $ range 1 5
    print $ range 5 1

range :: Integral a => a -> a -> [a]
range a b
    | a < b = [a..b]
    | otherwise = reverse [b..a]