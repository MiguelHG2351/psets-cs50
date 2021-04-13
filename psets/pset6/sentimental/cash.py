from cs50 import get_string
from math import isnan, ceil

def centavos(cash):
    return ceil(cash * 100)

def main():
    coins = [25, 10, 5, 1]
    while True:
        cash = get_string('\nIngrese el dinero en dolares, no centavos: ')
        try:
            cash = float(cash)
            break
        except:
            chash = ''

    cash = centavos(cash)
    total_coins = [0, 0, 0, 0]

    while cash != 0:
        if cash >= coins[0]:
            total_coins[0] = total_coins[0] + 1
            cash = cash - coins[0]

        elif cash >= coins[1]:
            total_coins[1] = total_coins[1] + 1
            cash = cash - coins[1]

        elif cash >= coins[2]:
            total_coins[2] = total_coins[2] + 1
            cash = cash - coins[2]

        elif cash >= coins[3]:
            total_coins[3] = total_coins[3] + 1
            cash = cash - coins[3]

    print(total_coins[0] + total_coins[1] + total_coins[2] + total_coins[3])


main()
