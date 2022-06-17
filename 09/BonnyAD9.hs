main = do
    print $ swap [1, 2, 3, 4, 5]

swap :: [a] -> [a]
swap (a:b:r) = b : a : swap r
swap a = a