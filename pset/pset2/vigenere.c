#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int asciiToStandar(int number);

// Obtienen los parámetros
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error");
        return 1;
    }
    // A 	B 	C 	D 	E 	F 	G 	H 	I 	J 	K 	L 	M 	N 	O 	P 	Q 	R 	S 	T 	U 	V 	W 	X 	Y 	Z
    // 0 	1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12 	13 	14 	15 	16 	17 	18 	19 	20 	21 	22 	23 	24 	25

    string secret = argv[1];

    int lengthk = strlen(secret);

    for (int n = 0; n < lengthk; n++)
    {
        if (!isalpha(secret[n]))
        {
            printf("Error");
            return 1;
        }
    }
    string frase = get_string("\nIngresa la palabra a cifrar\n");

    for (int i = 0, j = 0; i <= strlen(frase) - 1; i++)
    {
        int length = frase[i];
        if ((length >= 65 && length <= 90) || (length >= 97 && length <= 122))
        {
            // Verifica si esta en minúsculas o no
            int isLower = islower(frase[i]);
            // Longitud del secret
            int lengthSecret = strlen(secret);
            // Longitud del carácter del secret a cifrar
            int ascciiCodeSecret = asciiToStandar(secret[j]);
            // Longitud del carácter de la frase
            int asciiCodeFrase = asciiToStandar(frase[i]);
            // El algoritmo de cifrado
            int crypt = (asciiCodeFrase + ascciiCodeSecret) % 26;

            if (isLower)
            {
                frase[i] = crypt + 97;
            }
            else
            {
                frase[i] = crypt + 65;
            }

            j++;
            if (j == lengthSecret)
            {
                j = 0;
            }
        }
    }

    printf("ciphertext: %s\n", frase);

    return 0;
}

int asciiToStandar(int number)
{
    if (number >= 65 && number <= 90)
    {
        number -= 65;
        return number;
    }

    if (number >= 97 && number <= 122)
    {
        number -= 97;
        return number;
    }
    else
    {
        return number;
    }

    return number;
}