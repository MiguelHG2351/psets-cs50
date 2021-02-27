#include <string.h>
#include <cs50.h>
#include <math.h>

// librerias
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // funciona la coerción de tipos de JavaScript xD
    int num1 = fraction[0] - '0';
    int num2 = fraction[2] - '0';

    return num1 * 8 / num2;
}
// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };
    // Obtiene la nota principal y se agrega '\0' para que el strcmp devuelva falso y darle un fin al while
    char notaPrincipal[2] = {note[0], '\0' };
    int nota_final = 0; // Es la que va sumando todas las notas de la canción
    while (strcmp(NOTES[nota_final], notaPrincipal))
    {
        nota_final++;
    }

    // aplicando la fórmula frecuencia(nota,octava) := 440 * exp( (octava-4)+ ((nota-9)/12) *ln(2) )
    nota_final = nota_final - 9;

    // Si es sostenido se agrega la formula de la octava, según la formula
    if (note[1] == '#')
    {
        nota_final++;
        int octavas = note[2] - '0';
        nota_final += (octavas - 4) * 12;
    }
    // Si es bemol se convierte a la nota
    else if (note[1] == 'b')
    {
        nota_final--;
        int octavas = note[2] - '0';
        nota_final += (octavas - 4) * 12;

    }
    // Si no tiene una longitud mayor a 2 es por que no tiene '#' o 'b'
    else
    {
        int octavas = note[1] - '0';
        // se resta cuatro por la fórmula escrita anterior mente, luego se adapta a la nota * 12
        nota_final += (octavas - 4) * 12;
    }
    return round(pow(2.0, (float) nota_final / 12) * 440);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // Si hay espacio regresa falso
    int descanso = strcmp(s, "");
    if (descanso == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}