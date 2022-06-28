isLeap :: Int -> Bool
isLeap year = year `mod` 4 == 0

main :: IO ()
main = do
    print (if isLeap 2016 then "is" else "isn't")
