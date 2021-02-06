#include<stdio.h>

int sumar_dos_enteros(int, int); // Prototype

int main(void) {
    int numero1 = 45;
    // Imprime la función, se pasa una función como parametros, similar a  un callback pero no es.
    printf("%d", sumar_dos_enteros(numero1, numero1));
}

int sumar_dos_enteros(int num1, int num2) {
    return num1 + num2;
}
