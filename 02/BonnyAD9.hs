main = do
    print $ reverse' [1, 2, 3]

reverse' :: [a] -> [a]
reverse' [] = []
reverse' (a:r) = reverse' r ++ [a]