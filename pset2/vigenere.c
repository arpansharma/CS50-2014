/**
 * vigenere.c
 *
 * Arpan Sharma
 * arpan.sharma011@gmail.com
 *
 * Program that encrypts messages using Vigenère’s cipher.
 */


#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checking for number of command line arguments entered
    if (argc != 2 )
    {
        printf("Wrong Input !!");
        return 1;
    }
           
    else
    {
        string b = argv[1];
        int l1 = strlen(b);
        
        // checking the keyword for containing only alphabets
        for(int i = 0; i < l1; ++i)
        {
            if ( !(isalpha(b[i])))
            {
                printf("Wrong Input !!");
                return 1;
            }
        }
        
        
        string a = GetString();
        int l = strlen(a);
        
        // keeps a check on the index of the keyword
        int j = 0;
        
        int c;
        
        // loop for encrypting our message
        for(int i = 0; i < l; ++i)
        {
            // checking for the ith character in text to be a alphabet
            if (isalpha(a[i]))
            {
                // checking for the jth character in keyword to be uppercase
                if (isupper(b[j]))
                    c = b[j] - 65;
                    
                else
                    c = b[j] - 97;
                
                if (isupper(a[i]))
                {
                    c = (a[i] - 65 + c) % 26;
                    a[i] = c + 65;
                }
                
                else
                {
                    c = (a[i] - 97 + c) % 26;
                    a[i] = c + 97;
                }    
                
                
                //the letters in k must be reused cyclically as many times as it takes to encrypt p
                if (j == l1 - 1)
                    j = 0;
                else
                    ++j;
            }
        }
        
        // printing the final encrypted string
        printf("%s\n", a);
    }
}    
