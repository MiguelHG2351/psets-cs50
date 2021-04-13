#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdint.h>

// asignamos el tipo de dato BYTE
typedef uint8_t BYTE;

bool isjpg(BYTE *block);

int main(int argc, char *argv[])
{
    // validando que solo venga en los parámetros el nombre de archico comprimido
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
    // generamos un buffer de los nuevos archivos JPG
    FILE *JPG;

    // Analizan la información en bloques de 512 bytes por el formato FAT
    BYTE block[512];

    // buscas una imagen y verifica si ya esta analizando los datos de una imagen.
    bool foundjpg = false;
    // el bloque que se esta leyendo
    int readblock;
    int jpgnum = 0;
    // Entonces con el fread vamos leyendo de 512 en 512 bytes
    // En los casos que en la foto un bloque no tenga los 512 bytes se rellenan con ceros automaticamente (esto lo hace la camara)
    while (fread(block, sizeof(block), 1, inptr) == 1)
    {

        // buscamos en las cabeceras si es de tipo jpg
        if (isjpg(block))
        {

            // El nombre del archivo tendra tres dígitos + .jpg y un caracter nulo '\0'
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
        // Si no es jpg los primeros bytes pero uno de los bloques anteriores era jpg
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
// contexto https://www.ntfs.com/jpeg-signature-format.htm
bool isjpg(BYTE *block)
{
    // Son los números mágicos de un JPG.
    // block[0] == 0xff;
    // block[1] == 0xd8;
    // block[2] == 0xff;
    // block[3] == 0xe0;
    if (block[0] == 0xff &&
        block[1] == 0xd8 &&
        block[2] == 0xff &&
        block[3] == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}