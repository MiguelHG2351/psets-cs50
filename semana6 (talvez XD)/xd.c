#include<stdio.h>
#include<cs50.h>

int suma(int num, int num2, int num3);
int resta(int num, int num2, int num3);
int multp(int num, int num2, int num3);
float division(int num, int num2, int num3);

int main(void)
{
    int number[3];
    int sumar;
    int restar;
    int multiplicar;
    float dividir;

    for(int i = 0; i < 3; i++)
    {
        number[i] = get_int("Ingrese un número, %d restantes\n[", 3 - i);
        if(number[i] == 0)
        {
            i--;
        }
    }

    sumar = suma(number[0], number[1], number[2]);
    restar = resta(number[0], number[1], number[2]);
    multiplicar = multp(number[0], number[1], number[2]);
    dividir = division(number[0], number[1], number[2]);

    printf("La suma es: %d\n", sumar);
    printf("La resta es: %d\n", restar);
    printf("La multiplicacion es: %d\n", multiplicar);
    printf("La division es: %f\n", dividir);
}

int suma(int num, int num2, int num3)
{
    return num + num2 + num3;
}

int resta(int num, int num2, int num3)
{
    return num - num2 - num3;
}

int multp(int num, int num2, int num3)
{
    return num * num2 * num3;
}

float division(int num, int num2, int num3)
{
    return num / num2 / num3;
}
