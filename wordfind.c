#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define LENGTH 45

typedef struct node
{
    char* word;
    struct node* next;
} node;



int main(int argc, char* argv[])
{
    //ensure a file was given
    if (argc != 2)
    {
        printf("usage error. Correct usage: ./wordfind infile\n");
        return 1;
    }

    char* infile = argv[1];
    
    //open the file, check for null.
    printf("your infile was %s\n", infile);
    
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("could not open %s.\n", infile);
        return 2;
    }
    
    //keep track of words loaded
    int index = 0; 
    int found = 0; 
    char word[LENGTH+1];
    
    //read a char at a time, until the end of the file.
    for (int c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(inptr)) != EOF && isalpha(c));
                
                index = 0; 
            } 
            
             // ignore words with numbers (like MS Word can)
            else if (isdigit(c))
            {
                printf("found a number\n");
                
                // consume remainder of alphanumeric string
                while ((c = fgetc(inptr)) != EOF && c != isblank(c))

                index = 0;
            }
        }

        
        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';
           
           //print it 
           printf("%s\n", word);
           
            //reset index
            index = 0;

            // update counter
            found++;
            
        }
    }
    
    printf("found %i words.\n", found);
}
