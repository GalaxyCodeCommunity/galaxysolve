import Data.Int
import Data.Bits
import Data.Time

main = do
    currTime <- getCurrentTime
    let seed = floor $ utctDayTime currTime :: Int64
    let (_, arr) = rngArr seed 100
    print $ map (`mod` 100) arr

rngNext :: (Integral a) => Int64 -> (Int64, a)
rngNext s = (n, fromIntegral (shiftR n 32 + (n .&. 0xFFFFFFFF)))
    where n = (rngStep 19.rngStep (-5).rngStep 7) s

rngArr :: (Integral a) => Int64 -> a -> (Int64, [Int])
rngArr s 0 = (s, [])
rngArr s c = (nns, n : a)
    where
        (ns, n) = rngNext s
        (nns, a) = rngArr ns (c - 1)

rngStep :: Int -> Int64 -> Int64
rngStep s n
    | s > 0 = n `xor` shiftR n s
    | otherwise = n `xor` (shiftL n.abs) s
