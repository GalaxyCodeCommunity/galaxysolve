<?php
$ar = [1, 2, 3, 4];
print_r($ar);
$len=count($ar);
for($i=0;$i<$len/2;$i++){
    $temp = $ar[$i];
    $ar[$i] = $ar[$len-$i-1];
    $ar[$len-$i-1] = $temp;
}
print_r($ar)
?>