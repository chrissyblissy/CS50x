height = 24

while height < 0 or height > 23:
    # checks that the inputted values are integers
    # https://www.101computing.net/number-only/
    while True:
        try:
            height = int(input("Input height of pyramid: "))
            break
        except:
            height = 24

    for i in range(0, height):
        for space in range(i, height - 1):
            print(" ", end="")

        for hash in range(height - i - 2, height):
            print("#", end="")
        print()