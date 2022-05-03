isColorChar :: Char -> Bool
isColorChar char = char `elem` (['a'..'f'] ++ ['0'..'9'])

isColor :: String -> Bool
isColor target = (head target == '#') && (length (tail target) == 6) && length (filter isColorChar (tail target)) == 6

main = print( isColor "#ffx00f")
