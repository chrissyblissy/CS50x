# means command line arguments can be used
import sys

# checks that only 2 arguments have been given
if len(sys.argv) != 2:
    exit(1)

# exits the program if the key is not an integer
while True:
    try:
        key = int(sys.argv[1])
        break
    except:
        exit()

if key < 0:
    exit()
while key > 26:
    key -= 26

plaintext = input("plaintext: ")
print("ciphertext: ", end="")

for char in plaintext:
    """Cycles through each character in the plaintext and prints its ciphertext version."""
    char = ord(char)
    if char >= 65 and char <= 90:
        char += key
        if char > 90:
            char -= 26
        print(chr(char), end="")
    elif char >= 97 and char <= 122:
        char += key
        if char > 122:
            char -= 26
        print(chr(char), end="")
    else:
        print(chr(char), end="")

print()