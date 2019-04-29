// Helper functions for music
#include<stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    float numerator = fraction[0] - '0';
    float denominator = fraction[2] - '0';
    return 8 * (numerator / denominator);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
//Initialises the note difference n
    float n = 0;
//Runs checks on each note depending on the semi-notes between it and A
    if (note[0] == 'B')
    {
        n = n + 2;
    }
    else if (note[0] == 'C')
    {
        n = n - 9;
    }
    else if (note[0] == 'D')
    {
        n = n - 7;
    }
    else if (note[0] == 'E')
    {
        n = n - 5;
    }
    else if (note[0] == 'F')
    {
        n = n - 4;
    }
    else if (note[0] == 'G')
    {
        n = n - 2;
    }
//Checks for any accidentals and then changes the note difference by 12 per octave from A4
    for (int i = 1; i < strlen(note); i++)
    {
        if (note[i] == '#')
        {
            n++;
        }
        else if (note[i] == 'b')
        {
            n--;
        }
        else
        {
            n = n + ((note[i] - '4') * 12);
        }
    }

    float f = round(pow(2, (n / 12)) * 440);
    return f;
}

// Determines whether a string represents a rest
//which should return true if its input, a string, represents a rest in our machine-readable format, otherwise false.
bool is_rest(string s)
{
    if (strcmp("", s) != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
