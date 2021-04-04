#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover\n ");
        return 1;
    }


    FILE *infile = fopen("card.raw", "r");


    if (infile == NULL)
    {
        fprintf(stderr, "Could not open card.raw\n ");
        return 1;
    }

    FILE *outfile = NULL;

    unsigned char each_jpeg[512];
    char file_name[8];
    int counter = 0;


    bool check = false;


    while (fread(each_jpeg, 512, 1, infile) == 1)
    {

        if (each_jpeg[0] == 0xff && each_jpeg[1] == 0xd8 && each_jpeg[2] == 0xff && (each_jpeg[3] & 0xf0) == 0xe0)
        {
            if (check == true)
            {
                fclose(outfile);
            }
            else
            {
                check = true;
            }

            sprintf(file_name, "%03i.jpg", counter);
            outfile = fopen(file_name, "w");
            counter++;
        }

        if (check == true)
        {
            fwrite(&each_jpeg, 512, 1, outfile);
        }
    }


    fclose(infile);
    fclose(outfile);


    return 0;
}
