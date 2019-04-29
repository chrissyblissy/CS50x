// Recovers JPEGs from corrupted data

#include <stdio.h>
#include <stdlib.h>

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

    //Counts the number of JPEGs found
    int filenumber = -1;

    //Calculate length of card.raw
    fseek(inptr, 0, SEEK_END);
    int lenfile = ftell(inptr);
    fseek(inptr, 0, SEEK_SET);

    //Declare the buffer of unsigned byte value of 0 to 255
    unsigned char buffer[512];
    fread(buffer, 512, 1, inptr);

    for (int i = 0; i < lenfile; i += 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xD8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            filenumber++;
            char filename[6];
            sprintf(filename, "%03i.jpg", filenumber);
            outptr = fopen(filename, "w");
            fwrite(buffer, 512, 1, outptr);
            fclose(outptr);
        }

        fread(buffer, 512, 1, inptr);
        if (filenumber >= 0)
        {
            char filename[6];
            sprintf(filename, "%03i.jpg", filenumber);
            outptr = fopen(filename, "a");
            fwrite(buffer, 512, 1, outptr);
            fclose(outptr);
        }





    }


    // close infile
    fclose(inptr);
    return 0;
}