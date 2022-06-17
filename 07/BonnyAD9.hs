main = do
    print $ bcount "cau (mega (dobre)) (fakt jo)"
    print $ bcount "cau (mega (dobre)) (fakt jo"
    print $ bcount "cau (mega (dobre)) fakt jo)"

bcount :: Integral a => String -> a
bcount s = bcount' s 0 0

bcount' :: Integral a => String -> a -> a -> a
bcount' "" _ c = c
bcount' ('(':s) o c = bcount' s (o + 1) c
bcount' (')':s) o c
    | o == 0 = bcount' s o c
    | otherwise = bcount' s (o - 1) (c + 1)
bcount' (_:s) o c = bcount' s o c