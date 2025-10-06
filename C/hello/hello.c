#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //asks user for input
    string user_input = get_string("What is your name?");

    //prints hello with the users input
    printf("Hello, %s\n", user_input);
}
