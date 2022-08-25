NB. Worst time complexity: O(n^2)
NB. Average time complexity: O(n*log(n))
quickSort=:($:@:(#~ ] < {.) , (#~ ] = {.) , $:@:(#~ ] > {.))^:(>&0@:#)

echo quickSort 5 1 _3 9 6 5 0
