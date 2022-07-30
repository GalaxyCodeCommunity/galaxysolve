import Data.Char (ord)

dividers :: Int -> [Int]
dividers number = filter (\item -> number `mod` item == 0) [1..number]

findBest :: Int -> Int
findBest number = foldl (\cary item -> if (item + (number `div` item)) < (cary + (number `div` cary)) then item else cary) number (dividers number)

generateCode :: Int -> Char -> String
generateCode number operation = ">" ++ replicate (findBest number) '+' ++ "[<" ++ replicate (number `div` findBest number) operation ++ ">-]<." 

convertChar :: Char -> Int -> String
convertChar target last = 
    if ord target - last > 0 
    then generateCode (ord target - last) '+' 
    else generateCode (last - ord target) '-'

convert :: String -> Int -> String
convert target last 
    | null target = ""
    | otherwise = convertChar (head target) last ++ convert (tail target) (ord (head target))

main = print (convert "a" 0)
