#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    //asks user for input
    do
    {
        height = get_int("Height: ");
    }
    //rejects user input if it not between 1 and 8
    while (!(height >= 1 && height <= 8));

    int number = 1;
    while (true)
    {
        //prints the spaces for the alignment on the right
        for (int y = 0; y < height - 1; y++)
        {
            printf(" ");
        }
        //prints the "#"
        for (int x = 0; x < number; x++)
        {
            printf("#");
        }
        printf("\n");
        //decreases the number of spaces in each row by 1
        height--;
        //increases the number of "#" in each row by 1
        number++;
        //stops the program once there are no more spaces at the bottom of the image
        if (height == 0)
        {
            break;
        }
    }

}