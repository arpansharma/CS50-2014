/**
 * mario.c
 *
 * Arpan Sharma
 * arpan.sharma011@gmail.com
 *
 * Prints the half pyramid of mario using hashes.
 */
 


#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int Height;
    
    // asking height of the pyramid from the user
    do
    {
        printf("Height: ");
        Height = GetInt();
    }
    while (Height < 0 || Height > 23);
    
    
    // this variable keeps a check on the number of spaces to be printed
    int space = Height - 2;
    
    
    // loop for printing the half pyramid 
    for (int i = 1; i <= Height; ++i)
    {
        int j;
        
        // loop for printing the spaces
        for (j = 0; j <= space; ++j)
        {
            printf(" ");
        }
        
        
        // loop for printing the hashes
        for (int k = j; k <= Height; ++k)
        {
            printf("#");
        }
        
        // amount of spaces to be printed decreases by one each time
        --space;
        
        // in order to start printing from the new line
        printf("\n");
    }
}
