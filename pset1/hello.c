/**
 * File:    hello.c
 * 
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 1
 * 
 * Summary of File:
 * 
 *     Prompts user for their name then prints "hello, [user's name]".
 * 
 * Resources
 *     https://cs50.readthedocs.io/library/c/
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}