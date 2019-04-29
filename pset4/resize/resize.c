// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n must be a positive integer less than or equal to 100.\n");
        return 2;
    }
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

    // determine padding for scanlines
    int paddingread = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    fprintf(stdout, "paddingread = %i \n", paddingread);
    //Update outfile's new headers
    bi.biWidth *= n;
    printf("bi.biWidth = %i\n", bi.biWidth);
    bi.biHeight *= n;
    printf("bi.biHeight = %i\n", bi.biHeight);

    int paddingwrite = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingwrite) * abs(bi.biHeight);
    printf("bi.biSizeImage = %i\n", bi.biSizeImage);
    bf.bfSize = bi.biSizeImage + 54;
    printf("bf.bfSize = %i\n", bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < (abs(bi.biHeight) / n); i++)
    {

        for (int rewrite = 0; (rewrite / n) < 1; rewrite++)
        {

            // iterate over pixels in scanline
            for (int j = 0; j < (bi.biWidth / n); j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, paddingread, SEEK_CUR);

            // determine new padding for writing scanlines
            // create padding new scanlines
            for (int k = 0; k < paddingwrite; k++)
            {
                fputc(0x00, outptr);
            }
            // move input pointer back to beginning of the line
            fseek(inptr, -((3 * (bi.biWidth / n)) + paddingread), SEEK_CUR);


        }
        // move input pointer to the start of the new line to begin scanning
        fseek(inptr, ((3 * (bi.biWidth / n)) + paddingread), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
