#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    const char* word;
    struct node* next;
} node;

#define CAPACITY 5

int search_hash(const char* word);

int main(void)
{
    //initiate small hash table
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
            table[i]->word = NULL;
            table[i]->next = NULL;
            }
        } 
    
    int count = 0;
    
    for (int n = 0; n < CAPACITY; n++)
    {
      const char* word0 = "apt";
      const char* word1 = "act";
      const char* word2 = "bat";
      const char* word3 = "bee";
      const char* word4 = "cry";
              
      const char* newword = malloc(sizeof(const char)*4);
      strcpy(newword, word);
      
      int hash = hash_funct(word);
      node* ptr = table[hash];
      
      //if (ptr != NULL)
      while(true)
      {
        //check for insertion at head node. 
        if (ptr->word == NULL)
        {
            ptr->word = newword;
            break;
        }
        
        if(ptr->word != NULL && ptr->next == NULL)
        {
            node* new = malloc(sizeof(node));
            
            if(new == NULL)
            {
                printf("error, not enough memory.\n");
                free(new);
                break;
            }
            
            new->word = newword;
            new->next = NULL;
            ptr->next = new;
            count++;
            break;
        }

        ptr = ptr->next;
        count++; 
      }
      
      printf("stored %s in table %d link %d\n", word, hash, count);
      
      count = 0;
      
    }

    //search
    for (int t = 0; t<CAPACITY; t++)
    {
        printf("word to find:\n");
        char* findword = GetString();
        int key = hash_funct(findword);
        node* ptr = table[key];
        while(true)
        {   
           if(ptr == NULL)
           {
                printf("could not find word.\n");
                break;
           }
           
           if( strcmp(ptr->word, findword) == 0 )
           {
                printf("found word: %s\n", ptr->word);
                break;
           }
            
           if(ptr->next == NULL)
           {
                printf("couldn't find word.\n");
                break;
           }
           
           ptr = ptr->next;
        }
        
    }
    
    //free!


   for (int i = 0; i<CAPACITY; i++)
   {
        node* ptr = table[i];
        
        if (ptr == NULL)
        {
            printf("error, could not unload\n");
            return 1;
            break;
        } 
        
        while (ptr->next != NULL)
        {
            node* prev = ptr;
            ptr = prev->next;
 
            free(prev->word);
            free(prev);
        }

        if (ptr->word != NULL)
        {
            free(ptr->word);
        }
        
        free(ptr);
        
   }

}


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


