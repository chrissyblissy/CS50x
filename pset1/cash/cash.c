#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = -1; //Initiates change and intchange
    int intchange = 0;
    while (change < 0)
    {
        change = get_float("How much change is owed? "); //Asks for input
        change = round(change * 100);
        intchange = change; //Produces integer value for input
    }
    int coin_count = 0;

    while (intchange >= 25) //Checks for values larger than 0.25 cent
    {
        intchange = intchange - 25;
        coin_count++;

    }
    while (intchange >= 10) //Checks for values larger than 0.1 cent
    {
        intchange = intchange - 10;
        coin_count++;
    }
    while (intchange >= 5) //Checks for values larger than 0.05 cent
    {
        intchange = intchange - 5;
        coin_count++;
    }
    while (intchange >= 1) //Checks for values larger than 0.01 cent
    {
        intchange = intchange - 1;
        coin_count++;
    }
    printf("%i\n", coin_count); //Prints the number of coins required
}