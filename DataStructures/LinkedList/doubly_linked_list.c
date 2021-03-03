#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct node {
    int value;
    struct node* next; 
    struct node* prev; 
} node;

// Prototypes
node *create_new_node(int value);
node *insert_at_head(node **head, node *node_to_insert);
node *find_node(node *head, int value);
void remove_node(node **head, node *node_to_remove);
void insert_after_node(node *node_to_insert_after, node *newnode);
void free_list(node **head);
void print_list(node *head);

node *head = NULL;

// Main functions
int main(void)
{
    node *tmp;
    // Create 25 nodes and insert them at the list's head
    for (int i = 0; i < 26; i++) {
        tmp = create_new_node(i);
        insert_at_head(&head, tmp);
    }
    // Find a node with the value 13
    tmp = find_node(head, 13);
    printf("found node with value %d\n", tmp->value);
    // Insert a node after the found node
    insert_after_node(tmp, create_new_node(120));
    // Remove the list's head
    remove_node(&head, tmp);
    print_list(head);
    free_list(&head);   
    print_list(head);   
    return 0;
}

node *create_new_node(int value)
{
    // Malloc the node
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL) exit(1);
    // Set the node values
    newnode->value = value;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
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

void free_list(node **head)
{
    int count = 0;
    while (*head != NULL)
    {
        node *tmp = *head;
        *head = tmp->next;
        free(tmp);
        count++;
    }
    printf("%d nodes were freed.\n", count);
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
