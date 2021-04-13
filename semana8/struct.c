#include <stdio.h>
#include <string.h>
#include<cs50.h>

// Estructuras
    struct CD
    {
        string artista;
        string title;
        float price;
        int songs;
    } disco;

int main(void) {
    // struct discos1;
    disco.artista = "Pinocho";
    disco.title = "Canciones Bebé";
    disco.price = 1250;
    disco.songs = 16;

    printf("\t\tLas canciones: %s", disco.title);
    printf("\tTiene los siguientes datos:");
    printf("\tArtista: %s", disco.artista);
    printf("\tPrecio: %.2f", disco.price);
    printf("\t Canciones totales: %d", disco.songs);

    return 0;
}
