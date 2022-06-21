merge :: [Int] -> [Int] -> [Int]
merge first second 
    | not(null first) && not(null second) = [head first] ++ [head second] ++ merge (tail first) (tail second)
    | otherwise = first ++ second

main :: IO ()
main = do
    print (merge [1, 2] [5, 6])
