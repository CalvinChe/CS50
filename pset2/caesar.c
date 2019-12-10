/**
 * File:    caesar.c
 * 
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 2
 * 
 * Summary of File:
 * 
 *     A program that enables you to encrypt messages using Caesar's cipher.
 *     The user proveds a command-line argument on what the key
 *     of the secret message they'll provide will be.
 * 
 *     Caesar's formula:
 *     c[i] = (p[i] + k) % 26
 *     where:
 *     c[i]: encrypted cipher
 *     p[i]: plaintext
 *     k:    key (a non-negative integer)
 *     %26: (A or a) as 0, (B or b) as 1,..., and (Z or z) as 25.
 *     
 * 
 * Resources:
 *     https://cs50.readthedocs.io/library/c/
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    /* If user provides no cmd-line args, or two or more */
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    
    /* Check key for validity, must be an int */
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {    
            printf("Usage: %s key\n", argv[0]);
            return 1; 
        }
    }
    
    /* Convert key from string to int */
    int key = atoi(argv[1]);
    
    /* Check if key is positive */
    if (key < 0)
    {
        printf("Key most be positive");
    }
    
    string p = get_string("plaintext: ");
    
    /* Encrypt message */
    for (int i = 0, n = strlen(p); i < n; i++)
    {   
        char c = p[i];
        /* If char is uppercase */
        if (c > 64 && c < 91)
        {
            /* Decrement c to where A = 0 so we can apply Caesar's formula, then increment back to correct ASCII codes */
            p[i] = ((c - 65 + key) % 26) + 65; 
        }
        /* If char is lowercase */
        else if (c > 96 && c < 123) 
        {
            /* Decrement c to where A = 0 so we can apply Caesar's formula, then increment back to correct ASCII codes */
            p[i] = ((c - 97 + key) % 26) + 97;
        }
    }
    
    printf("ciphertext: %s\n", p);
    
    return 0;
}