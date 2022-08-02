main = print $ digitCount 37

digitCount :: Integer -> Integer
digitCount 0 = 1
digitCount a = (succ.floor.logBase 10.fromIntegral.abs) a
