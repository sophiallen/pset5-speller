#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(void)
{
    const char* word = "hello";
    int length = strlen(word)+1;
    char* copy[length];
    
    for(int i=0; i < length; i++)
    {
        copy[i] = word[i];
        toupper(copy[i]);
    }
    
    copy[length] = '\0';
    
    printf("your word was %s, now it's %s.\n", word, copy);
}
