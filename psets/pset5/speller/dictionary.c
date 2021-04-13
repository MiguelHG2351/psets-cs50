// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// prototypes
bool unload(void);
bool check(const char *word);
bool load(const char *word);
unsigned int size(void);
int hash_function(const char *word);

typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
} node;

// Global variables
// Declaramos el tamaño de la hash. Por lógica el tamaño deberia ser 26 por la cantidad total de letras en inglés
const int N = 26;
int total_size = 0;

node *myhashtable[N];

int hash_function(const char *word)
{
    int index = -1;
    int first_letter = (int)word[0];

    if(first_letter >= 65 && first_letter <= 90) {
        index = first_letter - 65;
    }

    if(first_letter >= 97 && first_letter <= 122) {
        index = first_letter - 97;
    }

    if(index == -1)
    {
        fprintf(stderr, "TypeError: index should be less than 26");
        return index;
    }

    return index;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    int position = hash_function(word);

    // buscamos la palabra dentro del bucket
    for(node *tmp = myhashtable[position]; tmp != NULL; tmp = tmp -> next)
    {
        if(strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *fptr = fopen(dictionary, "r");

    char tempword[LENGTH + 1];

    if(fptr == NULL) {
        unload();
        return false;
    }

    while(fscanf(fptr, "%s", tempword) != EOF)
    {
        node *bucket = malloc(sizeof(node));
        if(bucket == NULL)
        {
            printf("\nF in the chat\n");
            return false;
        }
        strcpy(bucket->word, tempword);
        total_size++;
        int index = hash_function(tempword);
        if(myhashtable[index] == NULL)
        {
            myhashtable[index] = bucket;
            bucket->next = NULL;
        }
        else if (myhashtable[index] != NULL)
        {
            bucket->next = myhashtable[index];

            myhashtable[index] = bucket;
        }
    }

    fclose(fptr);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(total_size >=0)
    {
        return total_size;
    }
    return total_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        while(myhashtable[i] != NULL)
        {
            node *tmp = myhashtable[i]->next;
            free(myhashtable[i]);
            myhashtable[i] = tmp;
        }
        // Por si ocurre algo en el while y todavia sigue habiendo memoria en el bucket
        if(myhashtable[i] != NULL)
        {
            fprintf(stderr, "Error: no se ha podido liberar memoria correctamente");
            return false;
        }
    }
    return true;
}
