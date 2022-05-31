-- awfull

smallest :: [Int] -> Int
smallest items = foldr (\ x y -> if x < y then x else y) (head items) items

count :: String -> [Int]
count = foldr (\ x y -> if x == '(' then (head y + 1) : tail y else if x == ')' then head y : [head (tail y) + 1] else y) [0, 0] 

countBrackets :: String  -> Int 
countBrackets target = smallest (count target)

main = print (countBrackets "(parek(rizek))(rizek)")
