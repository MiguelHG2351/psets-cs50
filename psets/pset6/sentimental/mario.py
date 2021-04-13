from cs50 import get_int


def main():

    height = 0
    while(True):
        height = get_int('Ingrese la altura de la piramide')
        if(height >= 0 and height <= 23):
            break

    if height == 0:
        return 'EOF'
    width = height + 1

    for i in range(height):
        for j in range(width):
            if j > height - i - 2:
                print('#', end="")
            elif j < width:
                print(' ', end="")
        print('')


main()
