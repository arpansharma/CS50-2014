/**
* 
* Arpan Sharma
* arpan.sharma011@gmail.com
* 
* Inputs a string and prints the initials in Upper Case
*/


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    string name = GetString();
    int length = strlen(name);
    
    if (length > 0)
    {
        printf("%c", toupper(name[0]));
        for (int i = 1; i < length; ++i)
        {
            char c = name[i];
            
            // Checking for space
            if (c == ' ')
            {
                printf("%c", toupper(name[i + 1]));
            }
        }
        
        // Printing new line
        printf("\n");
    }
}
