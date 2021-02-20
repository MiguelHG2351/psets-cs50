#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

// Como funciona:
/*
    Ingresas la frase
    Luego el avance
    Elige la cantidad de letras a desplazar
    si se adelanta más de Z || z se reinicia a la A || a y se adelantan los restantes
    Por ejemplo: xD, ciftra 5 más, seria: cH
*/

int main(int argc, string argv[])
{
    printf("Tenga en cuenta que los caracteres permitidos son solo los de caractér ingles\n");
    string frase = get_string("Ingrese la frase a cifrar\n");
    int crypto = 0;
    int length = strlen(frase);
    int stringToASCII;

    if(argc > 1) {
        crypto = atoi(argv[1]);
    } else {
        return 0;
    }

    if (length == 0)
    {
        printf("NO puede ingresar una cadena vacia");
        return 1;
    }
    if (crypto >= 1)
    {
        for (int i = 0; i <= length - 1; i++)
        {
            stringToASCII = frase[i];
            if (stringToASCII >= 97)
            {
                if (frase[i] + crypto > 122)
                {
                    // usa una variable temporal
                    int temp = ((stringToASCII + crypto) - 122) + 96;
                    frase[i] = temp;
                }
                else
                {
                    frase[i] = stringToASCII + crypto;
                }
            }
            else if (stringToASCII >= 65)
            {
                if (stringToASCII + crypto > 90)
                {
                    // usa una variable temporal
                    int temp = ((stringToASCII + crypto) - 90) + 65;
                    frase[i] = temp;
                }
                else
                {
                    frase[i] = stringToASCII + crypto;
                }
            }
        }

        printf("ciphertext: %s\n", frase);
        return 0;
    }
    printf("Los valores no pueden ser negativos, o no ingreso la cantidad de iteraciones");
    return 0;
}