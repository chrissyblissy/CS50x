// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLE 10000

// creates the structure for the nodes in the linked lists
typedef struct node
{
    char word[LENGTH];
    struct node *nextptr;
}node;

// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str)

{
    unsigned long hash = 5381;
    int c = *str;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % HASHTABLE; // returns hashkey
}
// creates hashtable of size [HASHTABLE]
struct node *hashtable[HASHTABLE] = {0};
// creates counter for the number of words in the dictionary
int numberofwords = 0;


// Returns true if word is in dictionary else false
bool check(__attribute__((unused)) const char *word)
{
    // creates an unsigned string to use to check the inputted word
    unsigned char *wordcheck = (unsigned char *)malloc(sizeof(char)*LENGTH);
    strcpy((char *)wordcheck, word);

    // turns the inputted word lowercase ready to be checked
    for (int i = 0; i < strlen((char*)wordcheck); i++)
    {

        wordcheck[i] = tolower(wordcheck[i]);
    }

    // works out the hashkey that matches the word in the dictionary
    int hashval = hash((char *)wordcheck);

    // creates a cursor to iterate over to check through linked list
    struct node *cursor;
    cursor = hashtable[hashval];
    while (cursor != NULL)
    {
        // returns true if inputted word matches one of the words in the linked list
        if (strcmp((char *)wordcheck, cursor -> word) == 0)
        {
            free(wordcheck);
            return true;
        }
        cursor  = cursor -> nextptr;
    }
    free(wordcheck);
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{


    // creates variables and structs
    int hashval;
    char word[LENGTH];
    struct node *new_node;

    FILE *inptr = fopen(dictionary,"r");

    // iterates over the dictionary until EOF
    while (fgets(word, LENGTH + 1, inptr) != NULL)
    {
        strtok(word, "\n");


        new_node = (struct node *)malloc(sizeof(struct node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            numberofwords++;

            // creates new node in hashtable at value of hashval
            hashval = hash(word);
            strcpy(new_node->word, word);
            if (hashtable[hashval] == 0)
            {
                hashtable[hashval] = new_node;
                new_node -> nextptr = NULL;
            }
            else
            {
                new_node -> nextptr = hashtable[hashval];
                hashtable[hashval] = new_node;
            }

        }

    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numberofwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    struct node *cursor, *tmp;

    for (int i = 0; i < HASHTABLE; i++)
    {
        cursor = hashtable[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor -> nextptr;
            free(tmp);

        }

    }

    return true;
}
