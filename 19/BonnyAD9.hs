main = print $ mergeSort [5, 1, -3, 9, 6, 5, 0]

-- Time complexity: O(n*log(n))
mergeSort :: (Ord a) => [a] -> [a]
mergeSort [] = []
mergeSort [a] = [a]
mergeSort r = merge (mergeSort a) (mergeSort b)
    where (a, b) = halve r

-- merges two sorted lists so that the resulting list is sorted
merge :: (Ord a) => [a] -> [a] -> [a]
merge [] a = a
merge a [] = a
merge (a:ar) (b:br)
    | a < b = a : merge ar (b:br)
    | otherwise = b : merge (a:ar) br

-- divides list into two even halves (second may be 1 larger)
halve :: [a] -> ([a], [a])
halve [] = ([], [])
halve [a] = ([], [a])
halve a = (take c a, drop c a)
    where c = length a `div` 2
