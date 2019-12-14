/**
 * File:    crack.c
 * 
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 2
 * 
 * Summary of File:
 * 
 *     A program that cracks five character long alphabetical DES-based hashed passwords.
 * 
 *     Restrictions
 *     1. Your program should only accept one command-line argument: a hashed password.
 *     2. Assume each password has been hased with C's Des-based (not MD5-based) crypt function
 *     3. Assume each password is no longer than five (5) characters.
 *     4. Assume that each password is composed entirely of alphabetical characters
 * 
 *     char *crypt(const chara *key, const char *salt)
 *         - Takes a key + a salt as parameters
 *         - Key is user typed password
 *         - Salt is a two-character from [a-zA-Z0-9./].
 *         - Append the salt value to the front of the plain text password
 *         
 * 
 * Resources:
 *     https://cs50.readthedocs.io/library/c/
*/

#include <crypt.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int unshift(int c);

int main(int argc, string argv[])
{
    /* If user provides no cmd-line args, or two or more */
    if (argc != 2)
    {
        printf("Usage: %s hash\n", argv[0]);
        return 1;
    }
    
    /* Check key for validity, must be alphanumeric */
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalnum(argv[1][i]) && !ispunct(argv[1][i]))
        {    
            printf("Usage: %s keyword\n", argv[0]);
            return 1; 
        }
    }
    
    /* Obtain the Salt */
    char key[2];
    strncpy(key, argv[1], 2);
    
    char pass[6];
    /* Check all 1 length alphabetical string i.e a,b,c,..., z */
    for (int i = 0; i < 52; i++)
    {       
        pass[0] = unshift(i);
        pass[1] = '\0';
        /* Check if encrypted password is equal to the right hash */
        if (strcmp(crypt(pass, key), argv[1]) == 0)
        {
            printf("%s\n", pass);
            return 0;
        }
        /* Check all 2 length alphabetical strings i.e aa, ab, ac,...,zz */
        for (int j = 0; j < 52; j++)
        {
            pass[1] = unshift(j);
            pass[2] = '\0';
            /* Check if encrypted password is equal to the right hash */
            if (strcmp(crypt(pass, key), argv[1]) == 0)
            {
                printf("%s\n", pass);
                return 0;
            }
            /* Check all 3 length alphabetical strings i.e aaa, aab, aac,..., zzz */
            for (int k = 0; k < 52; k++)
            {
                pass[2] = unshift(k);
                pass[3] = '\0';
                /* Check if encrypted password is equal to the right hash */
                if (strcmp(crypt(pass, key), argv[1]) == 0)
                {
                    printf("%s\n", pass);
                    return 0;
                }
                /* Check all 4 length alphabetical strings i.e aaaa, aaab, aaac,..., zzzz */
                for (int l = 0; l < 52; l++)
                {
                    pass[3] = unshift(l);
                    pass[4] = '\0';
                    /* Check if encrypted password is equal to the right hash */
                    if (strcmp(crypt(pass, key), argv[1]) == 0)
                    {
                        printf("%s\n", pass);
                        return 0;
                    }
                    /* Check all 5 length alphabetical strings i.e aaaaa, aaaab, aaaac,..., zzzzz */
                    for (int m = 0; m < 52; m++)
                    {
                        pass[4] = unshift(m);
                        pass[5] = '\0';
                        /* Check if encrypted password is equal to the right hash */
                        if (strcmp(crypt(pass, key), argv[1]) == 0)
                        {
                            printf("%s\n", pass);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

int unshift(int c)
{
    /* If char is uppercase */
    if (c > -1 && c < 26)
    {
        /* increment c to where the ascii code is right */
        return c + 65; 
    }
    /* If char is lowercase */
    else
    {
        /* increment c to where the ascii code is right */
        return c - 26 + 97;
    }
    
    return c;
}
