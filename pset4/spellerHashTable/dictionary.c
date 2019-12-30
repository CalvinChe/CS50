// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate space for new word
        node *new_word = malloc(sizeof(node));

        // Check if there is enough memory
        if (new_word == NULL)
        {
            unload();
            return false;
        }

        // Copy the word into the node
        strcpy(new_word->word, word);

        // Insert node into beginning of table, previous head is next on the list
        new_word->next = hashtable[hash(new_word->word)];

        // Set inserted Value is the new head.
        hashtable[hash(new_word->word)] = new_word;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    // For each linkedlist in the hash table
    for (int i = 0; i < N; i++)
    {
        node *head = hashtable[i];

        // If the linkedlist is not NULL delete it.
        if (head != NULL)
        {
            for (node *ptr = head; ptr != NULL; ptr = ptr -> next)
            {
                count++;
            }
        }
    }

    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *head = hashtable[hash(word)];

    if (head != NULL)
    {
        for (node *ptr = head; ptr != NULL; ptr = ptr -> next)
        {
            // byte by byte comparison of the characters in lower case, returns 0 if equal
            if (strcasecmp(ptr->word, word) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // For all 26 arraylists
    for (int i = 0; i < N; i++)
    {
        node *head = hashtable[i];

        // unload each node in an arraylist
        while (head != NULL)
        {
            node *next = head->next;
            free(head);
            head = next;
        }

        if (i == 25)
        {
            return true;
        }
    }
    return false;
}
