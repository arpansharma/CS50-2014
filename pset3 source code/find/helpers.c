/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    
    if (n < 0)
        return false;
        
    else
    {
        int begin = 0;
        int end = n - 1;
        int middle = (begin + end) / 2;
        
        while (begin <= end)
        {
            if (values[middle] == value)
                return true;
            
            else if (values[middle] < value)
                begin = middle + 1;
                
            else
                end = middle - 1;
                
            middle = (begin + end) / 2;             
        }
        
        return false;
        
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    int min;
    for(int i = 0; i < n; ++i)
    {
        min = i;
        for(int j = i + 1; j < n; ++j)
        {
            if (values[j] < values[min])
                min = j;
        }
       
        if (min != i)
        {
            int temp = values[i];
            values[i] = values[min];
            values[min] = temp;
        }
        
    } 
}
