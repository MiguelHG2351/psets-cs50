#include<stdio.h>
#include<cs50.h>

// Incompleto
int main(void)
{
    int cantidad = get_int("Ingrese la cantidad de números");
    int number[cantidad];

    for(int i = 0; i < cantidad;i++)
    {
        number[i] = get_int("Ingrese el número");
    }

    for(int i = cantidad-1; i >= 0; i++)
    {
        printf("\n%d\n", number[i]);
    }

    return 0;
}
