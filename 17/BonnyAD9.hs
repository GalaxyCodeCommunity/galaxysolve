import Data.List
import Data.Char

main = do print $ analyze "parek v rohliku" -- 'r'

analyze :: String -> Char
analyze str = chr
    where (chr, _) = (ganalyze.group.sort.map toLower.filter isAlpha) str

ganalyze :: [String] -> (Char, Int)
ganalyze [[]] = (' ', 0)
ganalyze [str] = (head str, length str)
ganalyze (f:r)
    | cnt > rcnt = (chr, cnt)
    | otherwise = (rchr, rcnt)
    where
        (rchr, rcnt) = ganalyze r
        (chr, cnt) = ganalyze [f]
