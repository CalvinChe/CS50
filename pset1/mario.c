/**
 * File:    mario.c
 * 
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 1
 * 
 * Summary of File:
 * 
 *     Recreation of the pyramids in Nintendo's Super Mario Brothers in text.
 *     Hashes will be used to replace bricks.
 *     Restrictions.
 *          1. The height must be between, 1 and 8, inclusive
 *          2. There should not be any spaces to the right of the pyramid
 *          3. The "gap" between adjacent pyramids is equal to the width of two hashes.
 *     Example of a 4 height pyramid:
 *             #  #
 *            ##  ##
 *           ###  ###
 *          ####  ####
 * 
 * Resources
 *     https://cs50.readthedocs.io/library/c/
*/
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /* Initialization */
    int height;
    
    /* Making sure Height must be between, 1 and 8, inclusive. */
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    /* Prints out the pyramid */
    for (int i = height - 1; i >= 0; i--)
    { 
        /* Print the left side of the pyramid */
        for (int j = 0; j < height; j++)
        {
            if (j >= i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        
        /* Print the gap between the pyramid */
        printf("  ");
        
        /* Print the right side of the pyramid */
        for (int k = i; k < height; k++)
        {
            if (k >= i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}