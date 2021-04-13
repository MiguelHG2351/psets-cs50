#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdint.h>

// asignamos 8 bytes para que sea divisble entre 4
typedef uint8_t byte;

bool isjpg(byte *block);

int main(int argc, char *argv[])
{
    // validando los parametros del main
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover card.raw\n");
        return 1;
    }

    // abrir el archivo a ejecutar
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    // generamos un buffer
    FILE *JPG;

    // archivo temporal.
    byte block[512];

    // buscas una imagen.
    bool foundjpg = false;
    int readblock;
    int jpgnum = 0;

    while (fread(block, sizeof(block), 1, inptr) == 1)
    {

        // buscamos en las cabeceras si es de tipo jpg
        if (isjpg(block))
        {

            // El nombre del archivo tendra tres dígitos + .jpg y un caracter nulo
            char filename[8];

            // escribe el texto del nombre del archivo
            sprintf(filename, "%03.3i.jpg", jpgnum);
            printf("processing file: %s\n", filename);

            if (foundjpg == true)
            {
                // Si ya hay un archivo procesandose de la línea 67 se ciera.
                fclose(JPG);
            }
            else
            {
                // Ya se agrega el primer jpg por que no habia uno antes.
                foundjpg = true;
            }

            // ahora abrimos un archivo con JPG
            JPG = fopen(filename, "w");
            fwrite(block, sizeof(block), 1, JPG);

            jpgnum++;
        }
        // Si no hay header en el archivo
        else
        {
            // verifica si se esta trabajando con el formato jpg
            if (foundjpg == true)
            {
                // añade todo el buffer al archivo
                fwrite(block, sizeof(block), 1, JPG);

            }
        }
    }
    // cerramos los archivos
    fclose(inptr);
    fclose(JPG);
}

// Si es jpg el archivo que se va a abrir
bool isjpg(byte *block)
{
    if (block[0] == 0xff &&
        block[1] == 0xd8 &&
        block[2] == 0xff &&
        (block[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}