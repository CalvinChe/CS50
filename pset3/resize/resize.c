/**
 * File:    resize.c
 *
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Dec 2019
 * Purpose: Created for CS50 EDX Problem Set 3
 *
 * Summary of File:
 *
 *     A program called resize that resizes (i.e., enlarges or shrinks) 24-bit uncompressed BMPs by a factor of f.
 *
 * Specification
 *     1. The program should accept exactly 3 command-line arguments
 *     2. The first argument ,f , must be a floating-point value in the range [0.0, 100.0]
 *     3. The second argument must be the name of a BMP to be resized.
 *     4. The third argument must be the name of the resized version to be written.
 *     5. If your program is not executed with such, it should remind the user of the correct usage, as with print
 *        and main should return 1;
 *     6. If your program uses malloc, it must not leak any memory.
 * 
 * Example
 *     ./resize 4 small.bmp large.bmp
 *
 * Resources:
 *     https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
 *     https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)
 *     https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-rgbtriple
*/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // Check for valid float
    float f = atof(argv[1]);
    if ((sscanf(argv[1], "%f", &f) != 1) || f < 0.0 || f > 100.0)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    // allocate storage for outfile BITMAPFILEHEADER & BITMAPINFOHEADER
    BITMAPFILEHEADER *rBF = malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *rBI = malloc(sizeof(BITMAPINFOHEADER));

    // update resized BITMAPFILEHEADER & BITMAPINFOHEADER with updated info
    rBI->biSize = bi.biSize;
    rBI->biWidth = bi.biWidth * f;
    rBI->biHeight = bi.biHeight * f;
    rBI->biPlanes = bi.biPlanes;
    rBI->biBitCount = bi.biBitCount;
    rBI->biCompression = bi.biCompression;
    // determine padding for scanlines
    int paddingOUT = (4 - (rBI->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    rBI->biSizeImage = ((sizeof(RGBTRIPLE) * rBI->biWidth) + paddingOUT) * abs(rBI->biHeight);
    rBI->biXPelsPerMeter = bi.biXPelsPerMeter;
    rBI->biYPelsPerMeter = bi.biYPelsPerMeter;
    rBI->biClrUsed = bi.biClrUsed;
    rBI->biClrImportant = bi.biClrImportant;

    rBF->bfType = bf.bfType;
    rBF->bfSize = rBI->biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    rBF->bfReserved1 = bf.bfReserved1;
    rBF->bfReserved2 = bf.bfReserved2;
    rBF->bfOffBits = bf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(rBF, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(rBI, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // enlarge the image
    if (f >= 1)
    {
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            fpos_t position;
            fgetpos(inptr, &position);
            for (int j = 0; j < f; j++)
            {
                fsetpos(inptr, &position);
                for (int k = 0; k < bi.biWidth; k++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    // iterate over pixels in scanline
                    for (int m = 0; m < f; m++)
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // add padding
                for (int m = 0; m < paddingOUT; m++)
                {
                    fputc(0x00, outptr);
                }
            }

            // skip over original padding, if any
            fseek(inptr, padding, SEEK_CUR);
        }
    }
    // shrink the image
    else
    {
        // initilize count to determine how much to shrink by
        float countX = f;
        float countY = f;
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                countX += f;
                if (countY >= 1)
                {
                    if (countX >= 1)
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        countX--;
                    }
                }
            }

            // add padding
            if (countY >= 1)
            {
                countY--;
                for (int m = 0; m < paddingOUT; m++)
                {
                    fputc(0x00, outptr);
                }
            }
            countY += f;
            countX = 0;

            // skip over original padding, if any
            fseek(inptr, padding, SEEK_CUR);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // free memory
    free(rBF);
    free(rBI);

    // success
    return 0;
}