#include<stdio.h>

int main(void) {
    /* Primer paso, generar un arreglo de los números de la tarjeta */
    /* Segundo paso, múltiplicar desde el penultimo */
    /* 14578148 145781487 */
    int array[8] = { 1, 4, 5, 7, 8, 1, 4, 8 };
    int numberLength = 8; /* Longitud del código de la tarjeta */
    int firstArray[10]; // arreglo con los valores impares
    int secondArray[10]; // Arreglo con los valores pares
    int j = 0;
    int k = 0;
    int ref = 0;

    for(int i = numberLength-1; i >= 0 ; i--) {
        if(ref % 2 == 0) {
            secondArray[j] = array[i] * 2;
            printf("\n%d\n", j);
            j++;
        } else {
            firstArray[k] = array[i] * 2;
            k++;
        }

        ref++;
    }

    for(int i = 0; i < 4;i++) {
        printf("\nXD %d\n", secondArray[i]);
    }

    return 0;
}
