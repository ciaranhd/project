// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>




// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 60000;

// Hash table
node *table[N];

//Global Variables
int total_words_dictionary = 0;



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hash_value = hash(word);

    if (table[hash_value] == NULL)
    {
        // Word does not exist
        return false;
    }
    else
    {
        node *head_ptr = table[hash_value];

        while (head_ptr != NULL)
        {
            if (strcasecmp(head_ptr -> word, word) == 0)
            {
                return true;
            }

            head_ptr = head_ptr -> next;
        }
    }

    return false;
}



/*
 * A case-insensitive implementation of the djb2 hash function.
 * Change NUM_BUCKETS to whatever your number of buckets is.
 *
 * Adapted by Neel Mehta from
 * http://stackoverflow.com/questions/2571683/djb2-hash-function.
 */

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    unsigned int count = 0;
    char tempword[LENGTH + 1] = {'\0'};
    unsigned int hashvalue;


    while(fscanf(file, "%s", tempword) != EOF)
    {    //Query the hash function
        hashvalue = hash(tempword);

        if((table[hashvalue]) == NULL)
        {
            //If table[hashvale] returns a null, i.e. there is no pointer within the array element
            //Create pointer head_ptr which points at a box of tpye node

            node *head_ptr = malloc(sizeof(node));

            // Another way: node **head_ptr = malloc(sizeof(node)); which will return the address of the pointer, which then can be saved straight into the array.


            //Ensure that there was enough memory for the creation of the pointer.
            if ((head_ptr) == NULL)
            {
                printf("Failed to Allocate Memory");
                return 1;
            }

            //Populate the node with i) dictionary word ii) pointer/address for next node in the linked list (as this is the first in the series, head_ptr -> next is NULL)
            head_ptr -> next = NULL;
            strcpy(head_ptr -> word, tempword);

            //We want to save the address of the pointer/address in the array for a given hash value
            table[hashvalue] = head_ptr;


            //keep a count for every word successfully uploaded into dictionary
            total_words_dictionary++;

        }
        // There is something already at the hash value in the array - therefore we need to link
        else
        {
            //table[hashvalue] effetively contains the address of the head_ptr. I will insert the new word at the start of the linked list
            //First create a temporary pointer tmp_ptr and pass the CURRENT head_ptr into it. This ensure that we don't break the chain.
            node *tmp_ptr = table[hashvalue];

            //Create the new head_ptr variable (just in the case above when the array element is zero) and create memory. Ensuring that memory allocation has been successful.
            node *head_ptr = malloc(sizeof(node));
            if(!(head_ptr))
            {
                printf("Failed to Allocate Memory");
                return 1;
            }

            // assign data to the newly created node struct
            strcpy(head_ptr -> word, tempword);
            head_ptr -> next = NULL;


            // link the pre-existing data with the newly created node
            head_ptr -> next = tmp_ptr;


            //We want to save the address of the pointer/address in the array for a given hash value
            table[hashvalue] = head_ptr;

            //keep a count for every word successfully uploaded into dictionary
            total_words_dictionary ++;
            //printf("Total Words in Dictionary: %i ", total_words_dictionary);
        }

    //printf("Total Words in Dictionary: %i ", total_words_dictionary);
    }

    fclose(file);
    //printf("Total Words in Dictionary: %i ", total_words_dictionary);
    return true;



}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return total_words_dictionary;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // I don't think this is correct.

    for (int i = 0; i < N - 1; i++)
    {
        free(table[i]);
        return true;
    }
    return false;
}
