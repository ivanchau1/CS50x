#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string key);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    //Checks if the user inputted a single command line arguement
    if (argc == 2)
    {
        for (int q = 0, t = strlen(argv[1]); q < t; q++)
        {
            //Checks if the user inputted only a number
            if (isdigit(argv[1][q]))
            {
                //Sends the number to the only_digits function to validate if it is a digit
                bool key = only_digits(argv[1]);
                if (key == true)
                {
                    //Converts the string into a int
                    int final_key = atoi(argv[1]);
                    //User inputs the text they would like to change
                    string plaintext = get_string("Plaintext: ");
                    //prints the ciphertext
                    printf("Ciphertext: ");
                    for (int a = 0, n = strlen(plaintext); a < n; a++)
                    {
                        char ciphertext = rotate(plaintext[a], final_key);
                        plaintext[a] = ciphertext;
                        //Formats the ciphertext
                        printf("%c", plaintext[a]);
                    }
                    printf("\n");
                    return 0;
                }
                else if (key == false)
                {
                    printf("Usage: ./caesar key\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string key)
{
    bool isdigit = false;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        //checks if the user input is a digit only
        if (isdigit(key[i]) && !isalpha(key[i]))
        {
            isdigit = true;
        }
        else
        {
            isdigit = false;
        }
    }
    return isdigit;
}

char rotate(char c, int n)
{
    char return_value = 0;
    //Separates lowercase, uppercase, and non-letter characters
    if (isalpha(c))
    {
        //Converts the uppercase letters
        if (isupper(c))
        {
            c = c - 65;
            return_value = ((c + n) % 26) + 65;
        }
        //Converts the lowercase letters
        if (islower(c))
        {
            c = c - 97;
            return_value = ((c + n) % 26) + 97;
        }
    }
    //Returns the remaining non-letter characters
    else if (!isalpha(c))
    {
        return_value = c;
    }
    return return_value;
}