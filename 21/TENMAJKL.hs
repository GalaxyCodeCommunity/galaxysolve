import Data.Bits (Bits(shiftR, xor, shiftL))
import Data.Time.Clock.POSIX (getPOSIXTime)

random :: Int -> (Int -> a) -> (a, Int)
random prev f = (f next, next)
    where next1 = prev `shiftL` 16 
          next2 = next1 `xor` (next1 `shiftR` 23)
          next3 = next2 `mod` 1000
          next = next3 `xor` (next3 `shiftL` 5)

randomReturn :: Int -> (Int -> a) -> a
randomReturn prev f = result
    where (result, next) = random prev f

-- do does not work :eyebrown:
main = 
    getPOSIXTime 
    >>= (\seed -> print (randomReturn (round seed) (\x -> "number is " ++ show x))) 
