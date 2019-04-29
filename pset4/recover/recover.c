// Recovers JPEGs from corrupted data

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: infile\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];
    FILE *outptr;

    // open pointer file and check that input file has been opened correctly
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }

    //Counts the number of JPEGs found, numbering from 0
    int filenumber = -1;

    //Declare the buffer of unsigned byte value of 0 to 255
    unsigned char buffer[512];

    while (fread(buffer, 512, 1, inptr) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xD8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            filenumber++;
            char filename[8];
            sprintf(filename, "%03i.jpg", filenumber);
            outptr = fopen(filename, "w");
            fwrite(buffer, 512, 1, outptr);
            fclose(outptr);
        }
        if (!(buffer[0] == 0xff && buffer[1] == 0xD8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
        {
            if (filenumber >= 0)
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", filenumber);
                outptr = fopen(filename, "a");
                fwrite(buffer, 512, 1, outptr);
                fclose(outptr);
            }
        }
    }

    // close infile
    fclose(inptr);
    return 0;
}