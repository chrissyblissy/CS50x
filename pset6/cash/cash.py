change = - 1
while change < 0:
    while True:
        try:
            change = float(input("How much change is owed? "))
            break
        except:
            change = -1

intchange = int(100 * change)
coin_count = 0

while (intchange >= 25):
    intchange -= 25
    coin_count += 1

while (intchange >= 10):
    intchange -= 10
    coin_count += 1

while (intchange >= 5):
    intchange -= 5
    coin_count += 1

while (intchange >= 1):
    intchange -= 1
    coin_count += 1

print(coin_count)