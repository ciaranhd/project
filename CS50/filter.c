#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int blue = image[i][j].rgbtBlue;
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int avg_colour = round((blue + red + green) / 3.0);

            image[i][j].rgbtBlue = avg_colour;
            image[i][j].rgbtRed = avg_colour;
            image[i][j].rgbtGreen = avg_colour;
        }
    }
    return;
}

// Reflect image horizontally - the j values/ width co-ordinates remain unchanged. The i values/height will be reflected, or negative
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE reflect_arr[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            reflect_arr[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            reflect_arr[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            reflect_arr[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
        }
    }


    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j].rgbtBlue = reflect_arr[i][j].rgbtBlue;
            image[i][j].rgbtRed = reflect_arr[i][j].rgbtRed;
            image[i][j].rgbtGreen = reflect_arr[i][j].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int total_blue;
    int total_red;
    int total_green;

    int row_adj;
    int col_adj;
    float count;

    int avg_blue;
    int avg_red;
    int avg_green;

    //height = 4;
    //width = 4;

    RGBTRIPLE copy_array[height][width];

    for (int i = 0; i < height; i++)
    {
        //printf("\n");
        for (int j = 0; j < width; j++)
        {
            //printf("%d ",image[i][j].rgbtGreen);
            //printf("%d ",image[i][j].rgbtRed);
            //printf("%d ",image[i][j].rgbtBlue);

            count = 0.0;
            total_blue = 0;
            total_red = 0;
            total_green = 0;

            for (row_adj = -1; row_adj < 2; row_adj++)
            {
                for (col_adj = -1; col_adj < 2; col_adj++)
                {
                    if (i + row_adj >= 0 && j + col_adj >= 0 && i + row_adj < height && j + col_adj < width)

                    {
                        total_blue = total_blue + image[i + row_adj][j + col_adj].rgbtBlue;
                        total_red = total_red + image[i + row_adj][j + col_adj].rgbtRed;
                        total_green = total_green + image[i + row_adj][j + col_adj].rgbtGreen;
                        count = count + 1;
                    }
                }
            }
            //printf("total blue: %d ", total_blue);
            //printf("Count blue: %f ", count);
            //printf("\n");



            avg_blue = round(total_blue / count);
            avg_red = round(total_red / count);
            avg_green = round(total_green / count);
            //printf("Average Blue: %i\n ", avg_blue);

            copy_array[i][j].rgbtBlue = avg_blue;
            copy_array[i][j].rgbtRed = avg_red;
            copy_array[i][j].rgbtGreen = avg_green;

        }
    }

    //printf("\n");
    //printf("total blue: %d ", total_blue);
    //printf("\n");

    for (int i = 0; i < height; i++)
    {
        //printf("\n");
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy_array[i][j].rgbtBlue;
            image[i][j].rgbtRed = copy_array[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy_array[i][j].rgbtGreen;

            //printf("%i ", image[i][j].rgbtRed);
        }
    }
    return;

}


/*
    BYTE total_blue;
    BYTE total_red;
    BYTE total_green;
    float count;
    RGBTRIPLE temp_arr[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            total_blue = 0;
            total_red = 0;
            total_green = 0;
            count = 0;
            for (int k = -1; k < 2; k = k + 1)
            {
                for (int z = -1; z < 2; z = z + 1)
                {
                    if (i + k < 0 || i + k > height -1 || j + z < 0 || j + z > width - 1)
                    {
                        if ( k == 1 && j == 1)
                        {
                            int end_count = count;
                        }
                    }
                    else
                    {
                        temp_arr[i][j].rgbtBlue = temp_arr[i][j].rgbtBlue + image[i + k][j + z].rgbtBlue;
                        temp_arr[i][j].rgbtRed = temp_arr[i][j].rgbtRed + image[i + k][j + z].rgbtRed;
                        temp_arr[i][j].rgbtGreen = temp_arr[i][j].rgbtGreen + image[i + k][j + z].rgbtGreen;
                        count = count + 1;
                        if ( k == 1 && j == 1)
                        {
                            int end_count = count;
                        }
                    }
                 }
            }
        }
    }
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_arr[i][j].rgbtBlue;
            image[i][j].rgbtRed = temp_arr[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp_arr[i][j].rgbtGreen;
        }
    }
    return;
}
*/

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // first create two 2-D arrays for the Kernels gX and gY for edge detection

    int gXarray[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gYarray[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    RGBTRIPLE copy_array[height][width];


    double gXtotal_blue;
    double gXtotal_red;
    double gXtotal_green;

    double gYtotal_blue;
    double gYtotal_red;
    double gYtotal_green;


    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            gXtotal_blue = 0;
            gXtotal_red = 0;
            gXtotal_green = 0;

            gYtotal_blue = 0;
            gYtotal_red = 0;
            gYtotal_green = 0;


            for (int x = 0; x < 3; x++)
            {

                int row_adj = x - 1;
                for (int y = 0; y < 3 ; y++)
                {
                    int col_adj = y - 1;
                    if (i + row_adj >= 0 && j + col_adj >= 0 && i + row_adj < height && j + col_adj < width)
                    {
                        gXtotal_blue = gXtotal_blue + image[i + row_adj][j + col_adj].rgbtBlue * gXarray[x][y];
                        gXtotal_red = gXtotal_red + image[i + row_adj][j + col_adj].rgbtRed * gXarray[x][y];
                        gXtotal_green = gXtotal_green + image[i + row_adj][j + col_adj].rgbtGreen * gXarray[x][y];

                        gYtotal_blue = gYtotal_blue + image[i + row_adj][j + col_adj].rgbtBlue * gYarray[x][y];
                        gYtotal_red = gYtotal_red + image[i + row_adj][j + col_adj].rgbtRed * gYarray[x][y];
                        gYtotal_green = gYtotal_green + image[i + row_adj][j + col_adj].rgbtGreen * gYarray[x][y];

                    }
                }
            }

            double expo = 2;
            copy_array[i][j].rgbtBlue = round(fmin(sqrt(pow(gXtotal_blue, expo) + pow(gYtotal_blue, expo)), 255));
            copy_array[i][j].rgbtRed = round(fmin(sqrt(pow(gXtotal_red, expo) + pow(gYtotal_red, expo)), 255));
            copy_array[i][j].rgbtGreen = round(fmin(sqrt(pow(gXtotal_green, expo) + pow(gYtotal_green, expo)), 255));

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy_array[i][j].rgbtBlue;
            image[i][j].rgbtRed = copy_array[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy_array[i][j].rgbtGreen;
        }
    }

    return;
}
