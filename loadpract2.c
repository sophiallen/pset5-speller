#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define CAPACITY 26

typedef struct node
{
    char* word;
    struct node* next;
} node;

int hash_funct(char* key);



int main(void)
{   
    //initiate array of nodes
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
        table[i]->word = NULL;
        }
    }

   for (int t = 0; t<5; t++)
   {
        //hash the word 
        int hash = hash_funct(key);
        printf("your word was %s, its hash is %d\n", key, hash);
         
        //create node to hold word
        node* newptr = malloc(sizeof(node));
       
        if (newptr == NULL)
        {
            printf("insufficient memory to create newptr.\n");
            free(newptr);
            return 3; 
        }
    
        //assign correct word to node, set next to null. 
        newptr->word = key; 
        newptr->next = NULL;
        
        //buffer and counter
        node* current = table[hash];    
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
    
    printf("stored %s in node %i, link %i\n", key, hash, count);
    
    }
    
    //free up memory
    for (int n= 0; n<CAPACITY; n++)
    { 
        node* ptr = table[n];
        
        while (ptr != NULL)
        {
            node* current = ptr;
            ptr = ptr->next;
            
            if (current->word != NULL)
            {
                free(current->word); 
            }
            
            free(current);      
        }         
    }

}



int hash_funct(char* key)
{
    int hash = toupper(key[0])- 'A';
    
    return hash%CAPACITY;
}



