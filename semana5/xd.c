#include<stdio.h>
#include<cs50.h>

int main(void) {
    int lineas;
    int refLinea;
    lineas = get_int("\nIngrese la cantidada de  \"*\" \n ");
    refLinea = lineas - 1;

    for (int space = 0; space <= refLinea; space++)
    {
        for (int j = 0; j <= (refLinea * 2); j++)
        {
            if(j < refLinea - space || j > refLinea + space)
            {
                printf(" ");
            } else {
                printf("*");
            }
            if(j == ((refLinea * 2))) {
                printf("\n");
            }
        }
    }

    return 0;
}

/*

Un *

lineas = 4

Número tiene que ser impar

lineas === 5


  *
 ***
*****

por cada espacio disminuyes 1




el 3 es el centro

lineas * 2 - 1


*/