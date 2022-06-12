up =:'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
low=:'abcdefghijklmnopqrstuvwxyz'
swapCase=:(i.~&(up,low) { ,~&(low,up))"0

echo swapCase 'aHOj37'