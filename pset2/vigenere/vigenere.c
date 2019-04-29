#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


int main(int argc, string argv[])
{
    //Checks for the correct number of arguments
    if (argc == 2)
    {
        //Turns the argument into the cipher key
        string key = argv[1];
        bool alphacheck = true;
        for (int i = 0; i < strlen(key); i++)
        {
            if (isalpha(key[i]) == false)
            {
                alphacheck = false;
            }
        }
        if (alphacheck == true)
        {
            //Asks for input from the user
            string s = get_string("plaintext:  ");
            printf("ciphertext: ");
            char c;
            int j = 0;
            //Loops over the string that the user has inputted
            for (int i = 0; i < strlen(s); i++)
            {
                if (j % 3 == 0)
                {
                    j = 0;
                }
                key[j] = tolower(key[j]);
                //Checks and prints cipher for uppercase letters
                if (s[i] >= 65 && s[i] <= 90)
                {
                    c = s[i] + key[j] - 97;
                    if (s[i] + key[j] - 97 > 90)
                    {
                        c -= 26;
                    }
                    printf("%c", c);
                    j++;
                }
                //Checks and prints cipher for lowercase letters
                else if (s[i] >= 97 && s[i] <= 122)
                {
                    c = s[i] + key[j] - 97;
                    if (s[i] + key[j] - 97 > 122)
                    {
                        c -= 26;
                    }
                    printf("%c", c);
                    j++;
                }
                //Prints cipher for any non-letter characters
                else
                {
                    printf("%c", s[i]);
                }
            }
        }
        else
        {
            return 1;
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