swap :: [Int] -> [Int]
swap target 
    | length target > 1 = [target !! 1] ++ [head target] ++ swap (tail (tail target))
    | otherwise = target

main :: IO ()
main = do
    print (swap [1..10])
