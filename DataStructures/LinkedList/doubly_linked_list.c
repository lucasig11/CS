#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"

// Main functions
int main(void)
{
    node *head = NULL;
    node *tmp;

    for (int i = 0; i < 26; i++) {
        tmp = create_new_node(i);
        insert_at_head(&head, tmp);
    }
    
    tmp = find_node(head, 13);
    printf("found node with value %d\n", tmp->value);

    insert_after_node(tmp, create_new_node(120));
    remove_node(&head, tmp);
    print_list(head);   
    return 0;
}

node *create_new_node(int value)
{
    node *result = malloc(sizeof(node));
    if (result == NULL) exit(1);
    result->value = value;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

node *insert_at_head(node **head, node *node_to_insert)
{
    node_to_insert->next = *head;
    if (*head != NULL) {
        (*head)->prev = node_to_insert;
    }
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
    if (newnode->next != NULL) {
        newnode->next->prev = newnode;
    }
    newnode->prev = node_to_insert_after;
    node_to_insert_after->next = newnode;
}

void remove_node(node **head, node *node_to_remove)
{  
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        (*head)->prev = NULL;
        return;
    } 
    node_to_remove->prev->next = node_to_remove->next;
    if (node_to_remove->next != NULL)
        node_to_remove->next->prev = node_to_remove->prev;

    free(node_to_remove);
    return;
}

void print_list(node *head)
{
    node *tmp = head;

    while (tmp != NULL) {
        printf(" %d => ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}
