main = do
    print $ isLeap 2016
    print $ isLeap 2017

isLeap :: Integral a => a -> Bool
isLeap a = a `mod` 400 == 0 || (a `mod` 4 == 0 && a `mod` 100 /= 0)