def isLeap(year):
    return print(year % 4 == 0 and (year % 100 != 0 or year % 400 == 0))

isLeap(2016)
isLeap(2017)
