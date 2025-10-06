#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //sums all red green and blue
            float total = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            //determines average
            int avg = round(total / 3);

            //sets each colour to the average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //using sepia formula, determines sepia for each colour
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            //sets sepia colour if result is beyond 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //sets sepia colour to the calculated number
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //temporary red variable
            int tmpRed = image[i][j].rgbtRed;
            //swaps utilizing the temporary variable
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tmpRed;

            //temporary green variable
            int tmpGreen = image[i][j].rgbtGreen;
            //swaps utilizing the temporary variable
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tmpGreen;

            //temporyary blue variable
            int tmpBlue = image[i][j].rgbtBlue;
            //swaps utilizing the temporary variable
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tmpBlue;

        }
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //creates a duplicate of the two-dimensional array
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int numBoxes = 0;
            float totalRed = 0;
            float totalGreen = 0;
            float totalBlue = 0;

            //loops through neighbouring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int xCoord = x + i;
                    int yCoord = y + j;

                    //checks if surrounding pixels is valid
                    if (xCoord < 0 || xCoord > (height - 1) || yCoord < 0 || yCoord > (width - 1))
                    {
                        continue;
                    }

                    //totals colour value
                    totalRed = totalRed + image[xCoord][yCoord].rgbtRed;
                    totalGreen = totalGreen + image[xCoord][yCoord].rgbtGreen;
                    totalBlue = totalBlue + image[xCoord][yCoord].rgbtBlue;

                    numBoxes++;
                }
            }
            //averages and sets in into copy array
            copy[i][j].rgbtRed = round(totalRed / numBoxes);
            copy[i][j].rgbtGreen = round(totalGreen / numBoxes);
            copy[i][j].rgbtBlue = round(totalBlue / numBoxes);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //sets image pixels to the copy pixels
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
