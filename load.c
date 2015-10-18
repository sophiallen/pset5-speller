#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LENGTH 45
#define CAPACITY 26

typedef struct node
{
    char* word;
    struct node* next;
} node;

int hash_funct(char* key);

int main(int argc, char* argv[])
{
    //open the dictionary
    if (argc != 2)
    {
        printf("usage error. Useage: ./load dictionary.txt\n");
        return 1;
    }
    
    char* infile = argv[1];
    
    printf("loading %s...\n", argv[1]);
    
    FILE* inptr = fopen(infile, "r");
    
    if (inptr == NULL)
    {
        printf("error, could not open file.\n");
        return 2;
    }  
    
    //initialize hash table 
    node* table[CAPACITY]; 
    
    for (int i = 0; i<CAPACITY; i++)
    {
        table[i] = malloc(sizeof(node));
        
        if (table[i] == NULL)
        {
            printf("not enough memory for table[%i]\n", i);
            free(table[i]);
            return 2; 
        }
        else
        {
        table[i]->next = NULL;
        }
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
        
        // when a whole word is found
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';
           
            //TODO input conflict, wordfind uses chars, while loadpract uses char*. Hmmm.....

            //hash the word 
            int hash = hash_funct(word);
            
            //create node to hold word
            node* newptr = malloc(sizeof(node));
       
            if (newptr == NULL)
            {
                printf("insufficient memory to create newptr.\n");
                free(newptr);
                return 3; 
            }

            char* newword = malloc(sizeof(char)*index);
            if (newword == NULL) 
            {
                printf("insufficient memory to create newword.\n");
                free(newword);
            }

            //assign correct word to node, set next to null. 
            strcpy(newword, word);
            
            newptr->word = newword;
            newptr->next = NULL;
            
            //buffer and counter
            node* current = malloc(sizeof(node));
            if (current == NULL)
            {
                printf("malloc error\n");
                free(current);
                return 4;
            }
            current = table[hash];    
            int count = 0; 
    
            while(true)
            {
                //check for insertion at head
                if (current->word == NULL)
                {
                    table[hash] = newptr;
                    break;
                }
            
                //check for insertion at tail. 
                if (current->word != NULL && current->next == NULL)
                { 
                    current->next = newptr; 
                    count++;
                    break;
                }
    
                //update current & count
                current = current->next; 
                count++; 
            }
            
            //reset index
            index = 0;

            // update counter
            found++;
            
        }
    }
    
    int size = found;
    
    
    fclose(inptr);
    printf("found %i words in dictionary.\n", size);
    
    
     //free up memory
    for (int n= 0; n<CAPACITY; n++)
    { 
        node* ptr = table[n];
        
        while (ptr != NULL)
        {
            node* current = ptr;
            ptr = ptr->next;
            
            free(current);      
        }         
    }
  
}


int hash_funct(char* word)
{
    int hash = toupper(word[0])- 'A';
    
    return hash%CAPACITY;
}

