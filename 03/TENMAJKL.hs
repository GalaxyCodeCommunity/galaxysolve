-- TODO unfinished

import Data.List (isSubsequenceOf, permutations)

isColorChar char = char `elem` (['a'..'f'] ++ ['0'..'9'])

isColor :: String -> Bool
isColor target = (head target == '#') && (length (tail target) == 6) && filter isColorChar (tail target)

main = print( isColor "#ffff00")
