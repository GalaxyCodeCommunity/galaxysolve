cislo = int(input())

for x in range(cislo-1):

    # pro začátek od čísla 1
    x+=1

    output = str(x) + ". "
    if x%3 == 0 and x%5 == 0:
        output += "fizzbuzz"
    elif x%5 == 0:
        output += "buzz"
    elif x%3 == 0:
        output += "fizz"
    
    print(output)
