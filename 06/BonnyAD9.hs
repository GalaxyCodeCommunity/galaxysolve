import Data.Char

main = do
    putStrLn $ swapCase "aHOj37"

swapCase :: String -> String
swapCase [] = []
swapCase (c:s) = chr (sc (ord c)) : swapCase s

sc :: Integral a => a -> a
sc a
    | a > 64 && a < 91 = a + 32
    | a > 96 && a < 123 = a - 32
    | otherwise = a