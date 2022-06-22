main = do
    print $ zip' [0, 1] [2, 3]

zip' :: [a] -> [a] -> [a]
zip' [] b = b
zip' a [] = a
zip' (a:ra) (b:rb) = a : b : zip' ra rb