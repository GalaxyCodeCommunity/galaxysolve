quickSort :: [Int] -> [Int]
quickSort array
    | null array = []
    | otherwise = 
        (if length lower == 1 then 
            lower 
        else 
            quickSort lower
        ) ++ [curent] ++ 
        (if length higher == 1 then
            higher 
        else quickSort higher
        )
    where curent = head array
          next = tail array
          (lower, higher) = half next (<= curent)

half :: [Int] -> (Int -> Bool) -> ([Int], [Int])
half array f = foldr 
    (\item (true, false) -> if f item then 
        (item : true, false)
    else 
        (true, item : false)
    ) ([], []) array

main = print (quickSort [5, 1, -3, 9, 6, 5, 0])
