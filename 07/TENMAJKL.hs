count :: String -> [Int]
count = foldl (\ y x -> if x == '(' then (head y + 1) : tail y else if x == ')' && head y > 0 then head y - 1 : [y !! 1 + 1] else y) [0, 0] -- chce se mi zvracet - zdenda polreich

countBrackets :: String -> Int 
countBrackets target = count target !! 1

main = print (countBrackets ")((cs)cs))")
