#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"

// Node definition
typedef struct node {
    int value;
    struct node* next;  
}node;

node *head = NULL;

// Main functions
int main(void)
{
    node *tmp;

    for (int i = 0; i < 26; i++) {
        tmp = create_new_node(i);
        insert_at_head(&head, tmp);
    }
    
    tmp = find_node(head, 13);
    printf("found node with value %d\n", tmp->value);

    insert_after_node(tmp, create_new_node(120));
    remove_node(&head, head);
    print_list(head);   
    return 0;
}

node *create_new_node(int value)
{
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL) return NULL;
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

node *insert_at_head(node **head, node *node_to_insert) // send **head, so we can change the *head;
{
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}

node *find_node(node *head, int value)
{
    node *tmp = head;
    while (tmp != NULL) {
        if (tmp->value == value) return tmp;
        tmp = tmp->next;
    }
    return NULL;
} 

void insert_after_node(node *node_to_insert_after, node *newnode)
{
    newnode->next = node_to_insert_after->next;
    node_to_insert_after->next = newnode;
}

void remove_node(node **head, node *node_to_remove)
{
    node *tmp = *head;
    
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        return;
    } 
    
    while(tmp != NULL && tmp->next != node_to_remove)
        tmp = tmp->next; 

    if (tmp == NULL) return;

    tmp->next = node_to_remove->next;

    free(node_to_remove);
    
    return;
}

void print_list(node *head)
{
    node *tmp = head;

    while (tmp != NULL) {
        printf("[ Value: %d  Next: %p ] => \n", tmp->value, (void *) tmp->next);
        tmp = tmp->next;
    }
    printf("\n");
}
