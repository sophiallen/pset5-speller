/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

#define LENGTH 45
#define CAPACITY 26

//node to hold words in linked list
typedef struct node
{
    char* word;
    struct node* next;
} node;

//initialize hash table 
node* table[CAPACITY]; 

//hash function that deals with const chars
int search_hash(const char* word)
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

//

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{ 
    int hash = search_hash(word);
    node* ptr = table[hash];
    
    while (true)
    {
        if(ptr == NULL)
        {
            return false;
            break;
        }
        
        if(strcasecmp(ptr->word, word) == 0)
        {
            return true;
            break;
        }
        
        if(ptr->next == NULL)
        {
            return false;
            break;
        }
        
        if (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    const char* infile = dictionary;
    FILE* inptr = fopen(infile, "r");
    
    if (inptr == NULL)
    {
        printf("error, could not open file.\n");
        fclose(inptr);
        return false;
    }  
    
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
    
    //keep track of words loaded
    int index = 0; 
    int size = 0; 
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

            //hash the word 
            int hash = search_hash(word);

            char* newword = malloc(sizeof(char)*(index+1));
            strcpy(newword, word);
           
            node* current = table[hash]; 
            int count = 0;
    
            while(true)
            {
                //check for insertion at head
                if (current->word == NULL)
                {
                    table[hash]->word = newword;
                    break;
                }
            
                //check for insertion at tail. 
                if (current->word != NULL && current->next == NULL)
                { 
                    node* newptr = malloc(sizeof(node));
                    newptr->word = newword;
                    newptr->next = NULL;
                    
                    current->next = newptr; 
                    count++;
                    break;
                }
    
                //update current & count
                current = current->next; 
                count++; 
            }
    
            //printf("stored %s in node %i, link %i\n", word, hash, count);
            
            //reset index
            index = 0;

            // update counter
            size++;
            
        }
    }
    
    fclose(inptr);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int loaded = 0; 

    for (int i=0; i<CAPACITY; i++)
    {
        node* newptr = table[i];
        
        while (newptr != NULL)
        {  
            char* data = newptr->word;
        
            if (data != NULL)
            {
                loaded++;
                newptr = newptr->next;
            } 
            else
            {
                break;
            }
        }        
    }

    return loaded;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
   for (int i = 0; i<CAPACITY; i++)
   {
        //make a pointer to remember where we are, aim it at the head. 
        node* ptr = table[i];
        
        //let's just check to see that it worked as it's supposed to...
        if (ptr == NULL)
        {
            return false;
        } 
        
        //check to see if there are linked nodes after it, free-ing as we go.
        while (ptr->next != NULL)
        {
            //remember where the old node was, move ptr to the new.
            node* prev = ptr;
            ptr = prev->next;
            
            //free up the old data and node. 
            free(prev->word);
            free(prev);
           
            //repeat
        }
        
        //if we got to this point, we must the the only link left. 
        //just in case, let's check to see if it has a word. 
        if (ptr->word != NULL)
        {
            free(ptr->word);
        }
        
        //then finally, free the last node. 
        free(ptr);
        
   }
   
   //if we got to this point, it worked!
   return true;
}
