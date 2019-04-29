#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // n is height of half-pyramid
    int n = 24;
    while (n > 23 || n < 0)
    {
        n = get_int("Height: "); //Asks user for the height of the pyramid
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n - 1; j++) //Loops and prints the number of space for that line
        {
            printf(" ");
        }
        for (int j = (n - 1) - i; j <= n; j++) //Loops and prints the number of hashes for that line
        {
            printf("#");
        }
        printf("\n"); //Starts the next line of the pyramid
    }
}