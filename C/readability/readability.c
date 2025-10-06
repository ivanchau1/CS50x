#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int letters_num(string text);
int words_num(string text);
int sentences_num(string text);
int grade_level(float letters_count, float words_count, float sentences_count);

int main(void)
{
    //Asks user for input
    string text = get_string("Text: ");
    // Calculates the number of letters in the input
    int letters_count = letters_num(text);
    //Calculates the number of words in the input
    int words_count = words_num(text);
    //Calculates the number of sentences in the input
    int sentences_count = sentences_num(text);
    //Calculates the grading level
    int Coleman_liau_index = grade_level(letters_count, words_count, sentences_count);

    printf("%i letters\n", letters_count);
    printf("%i words\n", words_count);
    printf("%i sentences\n", sentences_count);
    if (!(Coleman_liau_index <= 1 || Coleman_liau_index >= 16))
    {
        printf("Grade %i\n", Coleman_liau_index);
    }
    else if (Coleman_liau_index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int letters_num(string text)
{
    //Adds 1 to the variable letters if it finds a character that is in the alphabet
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int words_num(string text)
{
    //Adds 1 to the variable spaces if it finds a space within the input
    int spaces = 0;
    for (int a = 0, b = strlen(text); a < b; a++)
    {
        if (isspace(text[a]))
        {
            spaces++;
        }
    }
    //Plus 1 at the end as there is always 1 more word after the total number of spaces
    return spaces + 1;
}

int sentences_num(string text)
{
    //Adds 1 to the variable sentences if it finds a "." or "?" or "!" within the input
    int sentences = 0;
    for (int c = 0, d = strlen(text); c < d; c++)
    {
        if ((text[c] == 33) || (text[c] == 63) || (text[c] == 46))
        {
            sentences++;
        }
    }
    return sentences;
}
int grade_level(float letters_count, float words_count, float sentences_count)
{
    //Receives the total number of letters, words, and sentences and follows the formula to calculate the grading level
    float L = letters_count / words_count * 100;
    float S = sentences_count / words_count * 100;
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}