
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // readf
    float f = atof(argv[1]);

    if (f <= 0 || f > 100)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf1;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf1 = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi1;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi1 = bi;

    bi1.biWidth = floor(bi.biWidth * f);
    if (bi.biHeight >= 0)
    {
        bi1.biHeight = ceil(bi.biHeight * f);
    }
    else
    {
        bi1.biHeight = floor(bi.biHeight * f);
    }

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding1 = (4 - (bi1.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // The new size, in bytes, of the image
    bi1.biSizeImage = (bi1.biWidth * sizeof(RGBTRIPLE) + padding1) * abs(bi1.biHeight);

    // The new size, in bytes, of the bitmap file
    bf1.bfSize = bi1.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf1, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi1, sizeof(BITMAPINFOHEADER), 1, outptr);


    if (f >= 1)
    {
        int n = floor(f);
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < bi.biWidth; k++)
                {

                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile
                    for (int l = 0; l < n; l++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // add padding
                for (int m = 0; m < padding1; m++)
                {
                    fputc(0x00, outptr);
                }
                if (j < n - 1)
                {
                    fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
        }
    }
    else
    {
        int Dh = abs(bi.biHeight) / (abs(bi.biHeight) - abs(bi1.biHeight));
        int Dw = bi.biWidth / (bi.biWidth - bi1.biWidth);
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            if (i % Dh != 0)
            {

                // iterate over pixels in scanline
                for (int k = 0; k < bi.biWidth; k++)
                {

                    // temporary storage
                    RGBTRIPLE triple;

                    if (k % Dw != 0)
                    {
                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        // write RGB triple to outfile

                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                    }
                }
                // add padding
                for (int m = 0; m < padding1; m++)
                {
                    fputc(0x00, outptr);
                }
                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);
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