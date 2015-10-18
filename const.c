#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAPACITY 25

int search_hash(const char* word);
{
    int hash = 0;
   
    if (islower(word[0]))
    {
        hash = word[0] - 'a';  
    }
   
    else
    {
        hash = word[0] - 'A';
    }
    
    return hash%CAPACITY;
}
