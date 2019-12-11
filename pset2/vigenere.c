/**
 * File:    vigenere.c
 * 
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 2
 * 
 * Summary of File:
 * 
 *     A program that enables you to encrypt messages using Vigenere's cipher.
 *     The user proveds a command-line argument on what the key
 *     of the secret message they'll provide will be.
 * 
 *     Vigenere's formula:
 *     c[i] = (p[i] + k[j]) % 26
 *     where:
 *     c[i]: encrypted cipher
 *     p[i]: plaintext
 *     k[j]: key(an alphabetical string, where A(or a) represents 0, B (or b) represents 1)
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

int shift(char c);

int main(int argc, string argv[])
{
    
    /* If user provides no cmd-line args, or two or more */
    if (argc != 2)
    {
        printf("Usage: %s keyword\n", argv[0]);
        return 1;
    }
    
    /* Check key for validity, must be alphabetic */
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {    
            printf("Usage: %s keyword\n", argv[0]);
            return 1; 
        }
    }
    
    string p = get_string("plaintext: ");
    
    /* Encrypt message */
    for (int i = 0, j = 0, n = strlen(p); i < n; i++)
    {   
        /* If the key is shorter than the text, cycle through it */
        if (j == strlen(argv[1]))
        {
            j = 0;
        }
        
        int key = shift(argv[1][j]);
        char c = p[i];
        
        if (c > 64 && c < 91)
        {
            /* Decrement c to where A = 0 so we can apply Vigenere's formula, then increment back to correct ASCII codes */
            p[i] = ((c - 65 + key) % 26) + 65;
            j++;
        }
        /* If char is lowercase */
        else if (c > 96 && c < 123) 
        {
            /* Decrement c to where A = 0 so we can apply Vigenere's formula, then increment back to correct ASCII codes */
            p[i] = ((c - 97 + key) % 26) + 97;
            j++;
        }
    }
    
    printf("ciphertext: %s\n", p);
    
    return 0;
}

/* returns the positional integer value of a char (A or a would be 0, B or b would be 1,..., Z or z would be 25) */
int shift(char c)
{
    /* If char is uppercase */
    if (c > 64 && c < 91)
    {
        /* Decrement c to where A = 0 */
        return c - 65; 
    }
    /* If char is lowercase */
    else if (c > 96 && c < 123) 
    {
        /* Decrement c to where A = 0 */
        return c - 97;
    }
    
    return c;
}