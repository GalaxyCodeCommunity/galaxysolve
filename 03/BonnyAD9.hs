main = do
    print $ iscolor "#abcdef"

iscolor :: String -> Bool
iscolor ('#':r) = length r == 6 && foldr (\x a -> a && elem x "0123456789ABCDEFabcdef") True r
iscolor _ = False