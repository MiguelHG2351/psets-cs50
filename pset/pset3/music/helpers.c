#include <string.h>
#include <cs50.h>
#include <math.h>

// librerias
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num1 = atoi(fraction[0])
    int num2 = atoi(fraction[2])

    return num1 * 8 / num2;
}
// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };
    char notaPrincipal[2] = {note[0], '\0' };
    int nota_final = 0;
    while (strcmp(NOTES[nota_final], notaPrincipal))
    {
        nota_final++;
    }

    // aplicando la fórmula frecuencia(nota,octava) := 440 * exp( (octava-3)+ ((nota-9)/12) *ln(2) )
    nota_final = nota_final - 9;

    if (note[1] == '#')
    {
        nota_final++;
        int octavas = note[2] - '0';
        nota_final += (octavas - 4) * 12;
    }
    else if (note[1] == 'b')
    {
        nota_final--;
        int octavas = note[2] - '0';
        nota_final += (octavas - 4) * 12;

    }
    else
    {
        int octavas = note[1] - '0';
        nota_final += (octavas - 4) * 12;
    }
    return round(pow(2.0, (float) nota_final / 12) * 440);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
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