// Helper functions for music

#include <cs50.h>

#include "helpers.h"

struct Notes {
    char Do = '';
}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(s == '\0') return true
    return false
}
