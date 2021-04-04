#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4) //CHANGED 3 TO 4
    {
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
    }

    // N CHECK PART

    for(int  i = 0, z = strlen(argv[1]); i < z ; i++)
    {
        if(!isdigit(argv[1][i]))
        {
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
        }
    }
    int n = atoi(argv[1]);

    if(n < 0 || n > 100)
    {
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
    }


    // remember filenames
    char *infile = argv[2]; //CHANGED 1 TO 2
    char *outfile = argv[3]; //CHANGED 2 TO 3

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }


    // Modify the headers old to new


    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    int newWidth = oldWidth * n; // oo n=2 oooo
    int newHeight = oldHeight * n;

    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biHeight = newHeight;
    bi.biWidth = newWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * abs(newHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    RGBTRIPLE scanline[newWidth * sizeof(RGBTRIPLE)]; // OO OOOO 

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < n; k++)
            {
                scanline[(j * n) + k] = triple;
                
            }

        }
        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        // write the current scanline n times
        for (int j = 0; j < n; j++)
        {
            // write a new scanline once
            fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

            // write new padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success

    return 0;
}
