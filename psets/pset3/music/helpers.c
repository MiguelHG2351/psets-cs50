#include <string.h>
#include <cs50.h>
#include <math.h>

// Recordando como es que funcionaba esto v:
// Primero se inicia desde el principio
// La nota es una frecuencia, nice
// La nota se divide en 8 octavas, ok
// Las octavas en 12 semitono, ahí ta raro XD
// Estas son las octavas:
// Do=1, Do#=2, Re=3, Re#=4, Mi=5, Fa=6, Fa#=7, Sol=8, Sol#=9, La=10, La#=11, Si=12
// Si es un sostenido se aumenta uno por que esta después de la nota original
// Si es un bemol se disminuye uno por que afecta a la frecuencia reduciendo un semitono
// Una octava tiene 12 semitonos
// Ahora viene lo feo :,v
// Se toma la nota A4, como referencia
// frecuencia(nota,octava) := 440 * 2 ^((octava-3)+ ((nota-10)/12))
// Despejando el exponente ((octava-3)+ ((nota-10)/12)) queda = (((octava-3)*(12)) + (nota-10)/12)
// 12x(octava - 4) Será - 4 para indicarle la referencia de que la octava es 4 por A4 que es la nota de referencia
// nota - 9 Por que en los arreglos hay 12 notas pero en 11 posiciones por que se inicia a contar en cero
// Si es # se aumenta un número al resultado antes de dividirse sobre 12
// y resta un número si es bemol 'b'
// Ahí plantie el problema :D https://www.canva.com/design/DAEXqNUBi_0/vaB4AScgUW7LdKq7-ic0Fg/view?utm_campaign=designshare&utm_source=sharebutton
// librerias
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction) "1/8 1/4"
{
    // funciona la coerción de tipos de JavaScript xD
    // Encontre este método en stackoverflow
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
    // aplicando la fórmula frecuencia(nota,octava) := 440 * exp( (octava-3)+ ((nota-10)/12) *ln(2) )


    // Obtiene la nota principal y se agrega '\0' para que el strcmp devuelva falso y darle un fin al while
    char notaPrincipal[2] = {note[0], '\0' };
    int nota_final = 0; // Es la que va sumando todas las notas de la canción

    // Supongamos que la nota es D4, para este ejemplo :D
    // Use un while por que el for da error si no usas la variable local dentro de la condición
    while (true)
    {
        //
        if(strcmp(NOTES[nota_final], notaPrincipal)) {
            nota_final++; // aquí nedimos la distancia hasta A4
            // nota_final se detiene después de 3 recorridos
            // por que esta en la posición 3 del arreglo
            // nota_final = 3
        }
        else
        {
            break; // Aquí matamos al código XD
        }
    }

    // aplicando la fórmula nota-9 NO -10 por que los arrays inician en cero
    // Esto es por que A4, la nota central esta en la posicón 9
    nota_final = nota_final - 9;
    // Al restar 9 queda, nota_final = -6

    // Si es sostenido o bemol se agrega la formula de la octava, según la formula
    // Si es mayor a dos quiere decir que no es D4 puede ser D#4

    // D#4 -> nota D octava 4 semitono
    if(strlen(note) > 2)
    {
        // En vez de buscar en la posición 1 usamos la posición 2 por que en 1 esta # o b
        int semitono = note[2] - '0';
        nota_final += (semitono - 4) * 12;
    }
    if (note[1] == '#')
    {
        // # quiere decir que se quita una nota
        nota_final++;
    }
    else if(note[1] == 'b')
    {
        // b quiere decir que se quita una nota
        nota_final--;

    }
    // Si no tiene una longitud mayor a 2 es por que no tiene '#' o 'b'
    else
    {
        int semitono = note[1] - '0';
        // se resta cuatro por la fórmula escrita anterior mente, luego se adapta a la nota * 12
        // Aplicamos la fórmula de semitonos semitono - 4 * 12
        nota_final += (semitono - 4) * 12;
    }
    return round(pow(2.0, (float) nota_final / 12) * 440);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // Si hay una pausa regresa verdadero
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}