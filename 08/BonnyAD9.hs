main = do
    print $ fmap' 5 0 10 0 100
    print $ fmap' 65 50 100 0 255

fmap' :: Floating a => a -> a -> a -> a -> a -> a
fmap' x a b c d = (x - a) * (d - c) / (b - a) + c