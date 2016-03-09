/**
 * caesar.c
 *
 * Arpan Sharma
 * arpan.sharma011@gmail.com
 *
 * Program that encrypts messages using Caesar’s cipher.
 */


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // checking for number of command line arguments entered
    if (argc != 2 )
    {
        printf("You have done mischief in entering data !!");
        return 1;
    }
        
    else
    {
        int c;
        
        // contains the key by which the plain text has to be shifted
        int k = atoi(argv[1]);
        
        string a = GetString();
        int l = strlen(a);
                
        for(int i = 0; i < l; ++i)
        {
            // checking for the ith character in the text to be a alphabet
            if (isalpha(a[i]))
            {
                // checking for the ith character in the text to be uppercase
                if (isupper(a[i]))
                {
                    c = (a[i] - 65 + k) % 26;
                    a[i] = c + 65;
                }
                
                else
                {
                    c = (a[i] - 97 + k) % 26;
                    a[i] = c + 97;
                }
            }
            
         }
          
          // printing the final encrypted string
          printf("%s\n", a);
     }
          
}
