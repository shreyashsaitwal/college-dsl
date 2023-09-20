def check(num: int):
    if num % 2 == 0:
        print(f"{num} is an even number")
    else:
        print(f"{num} is an odd number")

num = input("Enter a number: ")
check(num)