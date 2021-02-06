#include <stdio.h> // printf y sprintf
#include <cs50.h> // printf y sprintf

// prototype
void enteroACadena(unsigned long long numero, char *bufer);

int main(){
    unsigned long long numero = get_long_long("Ya xd");
    char cadena[21]; // 21, XD

    enteroACadena(numero, cadena);

    for(int i = 0; i <= 10; i++) {
        printf("\n%c\n", cadena[i]);
    }
    printf("El entero %llu se convierte a '%s' como cadena", numero, cadena);
}

void enteroACadena(unsigned long long numero, char *bufer){
    // llu es para un long long unsigned.
    sprintf(bufer, "%llu", numero);
}