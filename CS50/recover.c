#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t  BYTE;
int count;
FILE *fpwrite;


int main(int argc, char *argv[])
{
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    char *filename = malloc(8);

    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // file == NULL is the same as !file
    if (!file)
    {
        return 1;
    }

    count = 0;
    while(fread(buffer, 512, 1, file) == 1)
    {

        //JPEG detected?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (count != 0)
            {
                fclose(fpwrite);
                sprintf(filename, "%03i.jpg", count);

                //create the pointer so that we may write from the buffer to the newly created filename.jpg. Note you can only create a pointer 'fpwrite' of type FILE when using fpopen
                fpwrite = fopen(filename, "w");

                // write to the file
                fwrite(buffer, 512, 1, fpwrite);
                count++;
            }

            // count is equal to 0
            else if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);

                //create the pointer so that we may write from the buffer to the newly created filename.jpg. Note you can only create a pointer 'fpwrite' of type FILE when using fpopen
                fpwrite = fopen(filename, "w");

                // write to the file
                fwrite(buffer, 512, 1, fpwrite);
                count++;
            }

        }

        else if (count != 0)
        {
            fwrite(buffer, 512, 1, fpwrite);
        }

    }
    // while the condition above is true the while loop will continue to execute. When we hit the 0 elements will be transferred to buffer, therefore fread() < 1
    fclose(file);
    free(filename);
    free(buffer);
    return 0;
}














/*
        else if (count != 0)
        {
            // a new JPEG is found, therefore we need to close the previous file which was written to from buffer, and start a new fie for the new image to write too instead
            fclose(fpwrite);
            sprintf(filename, "%03i.jpg", count);
            fpwrite = fopen(filename, "w");
            //write to file
            fwrite(buffer, 512, 1, fpwrite);
            count++;
        }
*/
