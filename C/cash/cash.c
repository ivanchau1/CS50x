#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    //Asks the user how much change is owed
    int change;
    do
    {
        change = get_int("Change Owed: ");
    }
    while (change < 0);
    return change;
}

int calculate_quarters(int cents)
{
    //Continues subtracting the amount the user inputted by 25
    int quarters_num = 0;
    while (cents >= 25)
    {
        cents = cents - 25;
        //records the number of quarters that was subtracted
        quarters_num++;
        //stops subtracting once the amount the user inputted is less than 25
        if (cents < 25)
        {
            break;
        }
    }
    return quarters_num;
}

int calculate_dimes(int cents)
{
    //Continues subtracting the amount (after it is less than 25) the user inputted by 10
    int dimes_num = 0;
    while (cents >= 10)
    {
        cents = cents - 10;
        //records the number of dimes that was subtracted
        dimes_num++;
        //stops subtracting once the amount the user inputted is less than 10
        if (cents < 10)
        {
            break;
        }
    }
    return dimes_num;
}

int calculate_nickels(int cents)
{
    //Continues subtracting the amount (after it is less than 10) the user inputted by 5
    int nickels_num = 0;
    while (cents >= 5)
    {
        cents = cents - 5;
        //records the number of nickels that was subtracted
        nickels_num++;
        //stops subtracting once the amount the user inputted is less than 5
        if (cents < 5)
        {
            break;
        }
    }
    return nickels_num;
}

int calculate_pennies(int cents)
{
    //Continues subtracting the amount (after it is less than 5) the user inputted by 1
    int pennies_num = 0;
    while (cents >= 1)
    {
        cents = cents - 1;
        //records the number of pennies that was subtracted
        pennies_num++;
        //Stops subtracting once the the amount the user inputted is equal to 0
        if (cents == 0)
        {
            break;
        }
    }
    return pennies_num;
}
