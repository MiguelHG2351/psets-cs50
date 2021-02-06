#include<stdio.h>
#include<cs50.h>

int centavos(float cash);

int main(void) {
    int coins[4] = {25, 10, 5, 1};
    float cash = get_float("Ingrese el dinero en dolares, no en centavos");
    int cashCentavos = centavos(cash);
    int returnCoins[4];
    coins[1] = coins[1] + cash;
    printf("%d", coins[1]++);

    return 0;
}

int centavos(float cash) {
    return cash * 100;
}
