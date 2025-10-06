// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 997;

// Hash table
node *table[N];

// Declared global variables
unsigned int number_words = -1;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Create hash value from word
    int hash_value = hash(word);

    // Point cursor to first node
    node *cursor = table[hash_value];

    // Go through linked list
    while (cursor != 0)
    {
        // Checks if word is in dictionary
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;

    // Totalling hash value froms characters in string
    for (int i = 0; i < strlen(word); i++)
    {
        total = total + toupper(word[i]);
    }

    // Returning index in linked list
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Opens dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        char word[LENGTH + 1];

        // Loops reading strings from file
        do
        {
            // Allocate memory
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }

            // Copy string into node
            strcpy(n->word, word);

            // Create index of location in linked list
            int hash_value = hash(word);
            n->next = table[hash_value];
            table[hash_value] = n;
            number_words++;
        }
        while (fscanf(file, "%s", word) != EOF);

        // Close file
        fclose(file);

        // Successfully read file
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (number_words > 0)
    {
        return number_words;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Runs through each bucket
    for (int i = 0; i < N; i++)
    {
        // Set cursor to start of linked list
        node *cursor = table[i];

        // While cursor do not equall null, free memory
        while (cursor != NULL)
        {
            // Set tmp equal to cursor
            node *tmp = cursor;
            // Set cursor eqaul to next word
            cursor = cursor->next;
            // Free tmp
            free(tmp);
        }
        // return true is memory freed was successful
        return true;
    }
    return false;
}
