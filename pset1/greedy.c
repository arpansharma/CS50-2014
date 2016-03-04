/**
 * greedy.c
 * 
 * Arpan Sharma
 * arpan.sharma011@gmail.com
 *
 * Asks the user how much change is owed and then spits out the minimum number of coins with which said change can be made.
 */
 
 

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    // to store the input from the user
    float change_input;
    
    // to store the number of coins
    int num_coins = 0;  
        
    
    printf("O hai! ");
    
    // taking input from the user
    do
    {
        printf("How much change is owed?\n");
        change_input = GetFloat();
    }
    while (change_input < 0);
    
    // converting input for our calculations
    int change = (int)round(change_input * 100);
    
    // checking for quarters
    if (change >= 25)
    {
        num_coins = num_coins + change / 25;
        change = change % 25;        
    }
    
    // checking for dimes
    if (change >= 10)
    {
        num_coins = num_coins + change / 10;
        change = change % 10;        
    }
    
    // checking for nickels 
    if (change >= 5)
    {
        num_coins = num_coins + change / 5;
        change = change % 5;        
    }
    
    // adding the left over pennies
    num_coins = num_coins + change;
    
    // printing the final number of coins
    printf("%d\n", num_coins);
    
}
