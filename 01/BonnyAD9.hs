main = do
    putStr $ fizzbuzz 16

fizzbuzz :: (Integral a, Show a) => a -> String
fizzbuzz 0 = ""
fizzbuzz n
    | n `mod` 15 == 0 = fizzbuzz (n - 1) ++ show n ++ " fizzbuzz\n"
    | n `mod` 3 == 0 = fizzbuzz (n - 1) ++ show n ++ " fizz\n"
    | n `mod` 5 == 0 = fizzbuzz (n - 1) ++ show n ++ " buzz\n"
    | otherwise = fizzbuzz (n - 1) ++ show n ++ "\n"