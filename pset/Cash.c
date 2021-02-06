#include<stdio.h>
#include<cs50.h>

int centavos(float cash);

int main(void) {
    int coins[4] = {25, 10, 5, 1};
    float cash = get_float("Ingrese el dinero en dolares, no en centavos");
    int cashCentavos = centavos(cash);
    int returnCoins[4] = {0, 0, 0, 0};

    while(true) {
        if(cashCentavos == 0) {
            break;
        }
        if(cashCentavos >= coins[0]) {
            cashCentavos = cashCentavos - coins[0];
            printf("%d\n", cashCentavos);
            returnCoins[0] = returnCoins[0] + 1;

        } else if(cashCentavos >= coins[1]) {
            cashCentavos = cashCentavos - coins[1];
            returnCoins[1] = returnCoins[1]+1;

        } else if(cashCentavos >= coins[2]) {
            cashCentavos = cashCentavos - coins[2];
            returnCoins[2] = returnCoins[2] + 1;

        } else if(cashCentavos >= coins[3]) {
            cashCentavos = cashCentavos - coins[3];
            returnCoins[3] = returnCoins[3] + 1;
        }
    }

    printf("Se devuelven: %d de %d¢ %d de %d¢ %d de %d¢ %d de %d¢", returnCoins[0], coins[0], returnCoins[1], coins[1], returnCoins[2], coins[2], returnCoins[3], coins[3]);

    return 0;
}

int centavos(float cash) {
    return cash * 100;
}
