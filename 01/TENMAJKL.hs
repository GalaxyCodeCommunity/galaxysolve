main = putStr ( foldr (\ x y -> show x ++ " " ++ (if x `mod` 3 == 0 then "fizz" else "") ++ (if x `mod` 5 == 0 then "buzz" else "") ++ "\n" ++ y) "" [1..100] )
