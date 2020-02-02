/**
 * File:    credit.c
 * 
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 1
 * 
 * Summary of File:
 * 
 *     A program that prompts the user for a credit card number and reports
 *     whether it is a valid American Express, MasterCard, or Visa card number
 *     using Luhn's algorithm.
 *     Luhn's algorithm:
 *      1. Multiply every other digit by 2, starting with the number’s second-to-last digit,
 *         and then add those products’ digits together.
 *      2. Add the sum to the sum of the digits that weren’t multiplied by 2.
 *      3. If the total’s last digit is 0
 *         (or, put more formally, if the total modulo 10 is congruent to 0),
 *         the number is valid!
 *     Differentiating between credit card companies:
 *      * American Express: 15-digit numbers, start with: 34 or 37
 *      * MasterCard:       16-digit numbers, start with: 51, 52, 53, 54, or 55
 *      * Visa :    13- and 16-digit numbers, start with: 4
 *      Note: Mastercard also have other potential starting numbers but we 
 *            won't concern ourselves with this problem.
 *            
 *     Example:
 *      $ ./credit
 *      Number: 4003600000000014
 *      VISA
 * 
 * Resources
 *    https://cs50.readthedocs.io/library/c/
*/
#include <cs50.h>
#include <stdio.h>

int length(long num);
long power(int x, int y);

int main(void)
{
    /* Init */
    long int ccNum = get_long("Number: ");
    long int ccNumCpy = ccNum;
    int len = length(ccNum);
    int sumEven = 0;
    int sumOdd = 0;
    
    /* Check if the CC number is valid */
    for (int i = 0; i < len; i++)
    {
        /* Seperate CC num to get every other digit */
        if (i % 2)
        {
            int value = ((ccNum % 10) * 2);
            int vLen = length(value);
            /* Add the products' digits together */
            for (int j = 0; j < vLen; j++)
            {
                sumOdd += value % 10;
                value /= 10;
            }
            ccNum /= 10;
        }
        else
        {
            /* Add the sum of the digits that were not multiplied */
            sumEven += (ccNum % 10);
            ccNum /= 10;
        }
    }
    
    /* Check if number is valid & company name*/
    if ((sumEven + sumOdd) % 10)
    {
        printf("INVALID\n");
    }
    else
    {
        /* Get the first & second digit */
        ccNumCpy = ccNumCpy / power(10, len - 1);
        int second = ccNumCpy % 10;
        int first = ccNumCpy / 10 % 10;
        
        /* Determine the company using the first digit */
        switch (first)
        {
            /* Check length and second number validity*/
            case 3:
                if (len != 15)
                {
                    printf("INVALID\n");
                    break;
                }
                switch (second)
                {
                    case 4:
                        printf("AMEX\n");
                        break;
                    case 7:
                        printf("AMEX\n");
                        break;
                    default:
                        printf("INVALID\n");
                        break;
                }
                break;
            case 4:
                if (len != 13 && len != 16)
                {
                    printf("INVALID\n");
                    break;
                }
                printf("VISA\n");
                break;
            case 5:
                if (len != 16)
                {
                    printf("INVALID\n");
                    break;
                }
                switch (second)
                {
                    case 1:
                        printf("MASTERCARD\n");
                        break;
                    case 2:
                        printf("MASTERCARD\n");
                        break;
                    case 3:
                        printf("MASTERCARD\n");
                        break;
                    case 4:
                        printf("MASTERCARD\n");
                        break;
                    case 5:
                        printf("MASTERCARD\n");
                        break;
                    default:
                        printf("INVALID\n");
                        break;
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
}

/* Returns the length of a long */
int length(long num)
{
    int len = 0;
    
    if (num == 0)
    {
        return 0;
    }
    
    do
    {
        len++;
        num /= 10;
    }
    while (num);
    
    return len;
}

/* Returns the power of x^y */
long power(int x, int y)
{
    if (y == 1)
    {
        return 1;
    }
    return x * power(x, y - 1);
}
