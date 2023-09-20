def is_vowel(c: str):
    vowels = ['a', 'e', 'i', 'o', 'u']
    if c.lower() in vowels:
        print(f"'{c}' is a vowel.")
    else:
        print(f"'{c}' is a consonant.")

c = input("Enter a character: ")

if len(c) > 1:
    print("Please enter a single character.")
else:
    is_vowel(c)