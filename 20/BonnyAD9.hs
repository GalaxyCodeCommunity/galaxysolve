main = print $ decompose 12 -- [2,2,3]

decompose :: Integral a => a -> [a]
decompose = dcmps 2

dcmps :: Integral a => a -> a -> [a]
dcmps i a
    | a <= 1 = []
    | a `mod` i == 0 = i : dcmps i (a `div` i)
    | otherwise = dcmps (i + 1) a
