import Data.Char (ord)

convertChar :: Char -> Int -> String
convertChar target last = 
    (
        if ord target - last > 0 
        then replicate (ord target - last) '+' 
        else replicate (last - ord target) '-'
    ) ++ "."

convert :: String -> Int -> String
convert target last 
    | null target = ""
    | otherwise = convertChar (head target) last ++ convert (tail target) (ord (head target))

main = print (convert "parek v rohliku" 0)
