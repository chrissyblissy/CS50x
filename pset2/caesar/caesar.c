#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Checks for the correct number of arguments
    if (argc == 2)
    {
        //Turns the argument into the cipher key
        int key = atoi(argv[1]);
        //Makes sure the key is between 1 and 26
        while (key > 26)
        {
            key = key - 26;
        }
        //Asks for input from the user
        string s = get_string("plaintext:  ");
        printf("ciphertext: ");
        char c;
        //Loops over the string that the user has inputted
        for (int i = 0; i < strlen(s); i++)
        {
            //Checks and prints cipher for uppercase letters
            if (s[i] >= 65 && s[i] <= 90)
            {
                c = s[i] + key;
                if (c > 90)
                {
                    c = c - 26;
                }
                printf("%c", c);
            }
            //Checks and prints cipher for lowercase letters
            else if (s[i] >= 97 && s[i] <= 122)
            {
                if (s[i] + key > 122)
                {
                    c = s[i] + key - 26;
                }
                else
                {
                    c = s[i] + key;
                }
                printf("%c", c);
            }
            //Prints cipher for any non-letter characters
            else
            {
                printf("%c", s[i]);
            }
        }
        printf("\n");
        return 0;
    }
    //Returns 1 if the user puts in the incorrect number of arguments
    else
    {
        printf("Incorrect number of arguments");
        printf("\n");
        return 1;
    }
}