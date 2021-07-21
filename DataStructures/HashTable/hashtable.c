#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256 
#define TABLE_SIZE 10   

// Data that will be stored in the table.
typedef struct person {
    char name[MAX_NAME];
    int age;
    struct person *next;
} person;

// Prototypes
void print_list();
void init_hashtable();
unsigned int hash (char *);
bool hash_table_insert(person *);
person *hash_table_delete(char *);
person *hash_table_find(char *);

// Create hash table.
person *hashtable[TABLE_SIZE];

unsigned int ITEM_COUNT = 0;

int main(void)
{
    init_hashtable();

    // insert a few random names
    person p = {.name = "Lula", .age = 70};
    hash_table_insert(&p);

    person a = {.name = "Karl", .age = 39};
    hash_table_insert(&a);

    person b = {.name = "Friedrich", .age = 67};
    hash_table_insert(&b);

    person c = {.name = "Vladimir", .age = 65};
    hash_table_insert(&c);

    person d = {.name = "Leon", .age = 34};
    hash_table_insert(&d);

    person e = {.name = "Kim", .age = 45};
    hash_table_insert(&e);

    person f = {.name = "Josef", .age = 35};
    hash_table_insert(&f);

    person g = {.name = "Luis", .age = 45};
    hash_table_insert(&g);

    person h = {.name = "Carlos", .age = 23};
    hash_table_insert(&h);

    person i = {.name = "Prestes", .age = 55};
    hash_table_insert(&i);

    // prints the 'complete' table
    print_list();

    // finds someone in the table
    person *tmp = hash_table_find("Lula");
    printf("Person %s with age %d found\n", tmp->name, tmp->age);

    // delete a few people
    printf("Deleting Josef, Vladimir and Kim.\n");
    hash_table_delete("Josef");
    hash_table_delete("Vladimir");
    hash_table_delete("Kim");

    // prints the new table
    print_list();
    return 0;
}

// Prints the hash table to sdout.
void print_list()
{
    unsigned int i;
    printf("\n======================================\n");
    for (i = 0; i < TABLE_SIZE; i++)
    {
        if (hashtable[i] == NULL){
            // check if head is empty
            printf("\t%d\t-----\n", i);
        } else {
            person *head = hashtable[i];
            person *tmp = head;
            printf("\t%d\t%s ", i, tmp->name);
            while(tmp->next != NULL)
            {
                printf("\t=>  %s ", tmp->next->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("======================================\n\n");
}

// Initialize the table.
void init_hashtable()
{
    ITEM_COUNT = 0;

    // Clear the table setting all the pointers to NULL
    for (size_t i = 0; i < TABLE_SIZE; i++)
        hashtable[i] = NULL;
}

// Hash the input to a location in the array.
unsigned int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % TABLE_SIZE;
}

// Returns the amount of items stored in the hash table
unsigned int size()
{
    return ITEM_COUNT;
}

// Insert in the table
bool hash_table_insert(person *p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    
    p->next = hashtable[index];
    hashtable[index] = p;

    return true;
}

// Delete from the table
person *hash_table_delete(char *name)
{
    // Pointer to list's head
    person **tmp = &hashtable[hash(name)];

    while ((*tmp) != NULL && strncasecmp((*tmp)->name, name, MAX_NAME) != 0)
        tmp = &(*tmp)->next;

    *tmp = (*tmp)->next;
    
    return *tmp; // return the pointer so it can be freed if it was allocated on the heap;
}

// Find in the table by name
person *hash_table_find(char *name)
{
    int index = hash(name);
    person *tmp = hashtable[index];

    while (tmp != NULL && strncasecmp(tmp->name, name, MAX_NAME) != 0)
        tmp = tmp->next;

    return tmp;
}
