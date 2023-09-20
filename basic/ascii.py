char = input("Enter a character: ")
if len(char) > 1:
    print("Please enter a single character.")
else:
    print(f"ASCII value of {char} is: {ord(char)}")