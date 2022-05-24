import Data.Char (ord, chr)

convert :: Char -> Char 
convert character
    | character >= 'a' && character <= 'z' = chr ( ord character - 32 )
    | character >= 'A' && character <= 'Z' = chr ( ord character + 32 )    
    | otherwise = character

swap :: String -> String
swap = map convert

main = print (swap "pAr1Ek512sfd7sd5A7SD")
