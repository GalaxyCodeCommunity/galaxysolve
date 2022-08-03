# 1. Solution wih a simple code
number = int(input("Enter a number: "))
for num in range(1,number):
    string = ""
    if num % 3 == 0:
        string = string + "Fizz"
    if num % 5 == 0:
        string = string + "Buzz"
    if num % 5 != 0 and num % 3 != 0:
        string = string + str(num)
    print(string)


# 2. Solution with Lambda function
# print(*map(lambda i: 'Fizz'*(not i%3)+'Buzz'*(not i%5) or i, range(1, number)),sep='\n')

