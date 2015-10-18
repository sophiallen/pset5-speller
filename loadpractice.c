#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int hash_function(char* key);

typedef struct node
{
    int hash;
    char* entry[10];
    struct node* next;
    struct node* prev;
} node;

#define SIZE 45
#define CAPACITY 26

void init_table( node*[]);

int main(void)
{
    //establish hash table
    node* table[CAPACITY];
    
    //set table's initial nodes to next=NULL
    init_table(table);
    
    //get practice words to hash & load
    char* key[10] =  GetString();
    printf("%s\n", key);
    
    //get hash value for the word. 
    int hash = hash_function(key);
    printf("%i\n", hash);
    
    //create new node for the word, check for null. 
    node* newptr = malloc(sizeof(node));
    if (newptr == NULL)
    {
        free(newptr);
        return 1;
    }
    
    //initialize the node that will hold the word. 
    newptr->next = NULL;
    newptr->entry = key; 
    
    //go to the correct  node in the table, check for null, if so, make newptr the new head. 
    if (table[hash]->next == NULL)
    {
        table[hash] = newptr; 
    }
    
    //if the head spot is taken, append to the head. 
    else
    {
        table[hash]->next = newptr;
    }
    
    //print list results
    node* current = table[hash];
    
    while (current != NULL)
    {
        printf("%s\n", current->entry);
        current = current->next;
    }
    
    //free memory
    free(predptr);
    free(newptr);
    free(current);
    
    for (int n = 0; n < CAPACITY; n++)
    {
        free(table[n]);
    }
    
}   

void init_table(node*[CAPACITY])
{
    node* table[CAPACITY] = argc[0];
    
    node* first = malloc(sizeof(node));
    if (first == NULL)
    {
        printf("not enough space\n");
        free(first);
    }
    first->next = NULL;

    for (int i = 0; i < CAPACITY; i++)
    {
        table[i] = first;
    }
    
    free(first);
    return;
}

int hash_function(char* key)
{

    int hash = toupper(key[0])- 'A';
    
    return hash%SIZE;
}
