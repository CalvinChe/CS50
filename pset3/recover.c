/**
 * File:    recover.c
 *
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 3
 *
 * Summary of File:
 *
 *     A program called recover that recovers JPEGs from a forensic image.
 *
 * Specification
 *     1. The program should accept exactly 1 command-line arguments
 *
 * Example
 *     ./recover card.raw
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // check command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open memory card file
    FILE *RAWptr = fopen(argv[1], "r");
    if (RAWptr == NULL)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 2;
    }

    // init storage
    unsigned char buffer[512];
    char *newFile = malloc(3 * sizeof(int) + 4 * sizeof(char) + 1);
    FILE *img;
    int count = 0;
    bool found = false;

    //read 512 bytes & repeat until the end of the file
    while (fread(buffer, 512, 1, RAWptr))
    {
        // check if valid JPEG using a bitwise AND operator
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xFF &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if this is not the first JPEG found
            if (found)
            {
                fclose(img);
            }
            // open a new JPEG
            sprintf(newFile, "%03i.jpg", count);
            img = fopen(newFile, "w");
            count++;
            found = true;
            // write the first 512 bytes of a JPEG into new file
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
        // write the rest of the JPEG file
        else if (found)
        {
            // write 512 bytes into new file
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
    }

    // close rawFile
    fclose(RAWptr);
    fclose(img);

    // free memory
    free(newFile);

    // success
    return 0;
}