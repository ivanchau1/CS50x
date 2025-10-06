#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Checks to see if user entered more than one image
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //Opens file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    BYTE bytes[512];
    char *filename = malloc(8 * sizeof(char));
    int jpg_counter = 0;
    FILE *JPG;
    //Reads 512 bytes
    while (fread(bytes, 512, 1, file))
    {
        //determines if it is a jpg
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            //Checks to see if it is start of new jpg
            if (jpg_counter != 0)
            {
                fclose(JPG);
            }
            //If first, writes first file
            sprintf(filename, "%03i.jpg", jpg_counter++);
            JPG = fopen(filename, "w");
            fwrite(bytes, 512, 1, JPG);
        }
        //if it is not first, continues writing
        else if (jpg_counter > 0)
        {
            fwrite(bytes, 512, 1, JPG);
        }
    }
    free(filename);
    fclose(file);
    fclose(JPG);
}