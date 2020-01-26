// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Returns a number between 0 and 26 dependsing on the letter
unsigned int location(const char letter)
{
    if (letter == '\'')
    {
        return 26;
    }

    return tolower(letter) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // temp ptr to store the head of the tree
        node *ptr = root;

        // iterate through the trie with your word
        for (int i = 0; word[i] != '\0'; i++)
        {
            int index = location(word[i]);

            // Determine if child pointer exists
            if (ptr->children[index] == NULL)
            {
                // if child pointer doesn't exist allocate space for new child
                node *new_child = malloc(sizeof(node));
                if (new_child == NULL)
                {
                    return false;
                }
                new_child->is_word = false;
                for (int j = 0; j < N; j++)
                {
                    new_child->children[j] = NULL;
                }

                // having root point to new child.
                ptr->children[index] = new_child;
            }

            // move pointer to new node
            ptr = ptr->children[index];
        }

        // at end of word, is_word is true
        ptr->is_word = true;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in the child
unsigned int sizeHelper(node *child)
{
    unsigned int count = 0;

    if (child->is_word)
    {
        count++;
    }

    for (int i = 0; i < N; i++)
    {
        if (child->children[i] != NULL)
        {
            count += sizeHelper(child->children[i]);
        }
    }

    return count;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (root->children[i] != NULL)
        {
            count += sizeHelper(root->children[i]);
        }
    }

    return count;

}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *ptr = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = location(word[i]);

        if (ptr->children[index] == NULL)
        {
            return false;
        }

        // move pointer to new node
        ptr = ptr->children[index];
    }

    if (ptr->is_word)
    {
        return true;
    }

    return false;
}

// Unloads the memory of the children
void unloadHelper(node *ptr)
{
    for (int i = 0; i < N; i++)
    {
        if (ptr->children[i] != NULL)
        {
            unloadHelper(ptr->children[i]);
        }
    }

    free(ptr);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (root->children[i] != NULL)
        {
            unloadHelper(root->children[i]);
        }
    }

    free(root);

    return true;
}
