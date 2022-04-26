rev :: [Int] -> [Int] 
rev target = (if length target > 1 then rev (tail target) else []) ++ [head target]

main = print (rev [1..50])
