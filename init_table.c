#include <stdio.h>
#include <stdlib.h>

#define CAPACITY = 26;

typedef struct node
{
    char* word;
    struct node* next;
    
} node; 

node* init_table(int capacity);

int main(void)
{
    node* table = init_table(26);
    
    table[0]->word = "apple"; 
    
    printf("your word was %s\n", table[0], word);
}

node* init_table(int capacity)
{
    node* table[capacity];
    
    for (int i = 0; i<capacity; i++)
    {
        table[i] = malloc(sizeof(node));
        
        if (table[i] == NULL)
        {
            printf("not enough memory for table[%i]\n", i);
            free(table[i]);
        }
        
        else
        {
        table[i]->next = NULL;
        }
    }
    
    return table;
}
