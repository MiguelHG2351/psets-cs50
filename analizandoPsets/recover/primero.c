#include<stdio.h>
#include<cs50.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    int data = 4;

    if(argc != 2) {
        fprintf(stderr, "Usage: recover card.raw\n");
        return 1;
    }
    printf("Hello World\n");
    // esto devuelve null porque no apunta a ningun archivo
    // FILE *input;

    // Son 512 bytes formato FAT dividen la información en bloque de 512

    int result = 55;
    int count = 0;

    printf("\n%.5i\n", 10);
    printf("\n%.5i\n", 3);
    printf("\n%.5i\n", 50);

    return 0;
}
