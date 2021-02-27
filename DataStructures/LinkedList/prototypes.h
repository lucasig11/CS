#ifndef PROTOTYPE_H
#define PROTOTYPE_H

// Node definition
typedef struct node {
    int value;
    struct node* next; 
    struct node* prev; 
}node; 

// Prototypes
node *create_new_node(int value);
node *insert_at_head(node **head, node *node_to_insert);
node *find_node(node *head, int value);
void remove_node(node **head, node *node_to_remove);
void insert_after_node(node *node_to_insert_after, node *newnode);
void print_list(node *head);

#endif
