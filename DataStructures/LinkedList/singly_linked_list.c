#include <stdio.h>
#include <stdlib.h>

// Type definitions
typedef struct node {
    int value;
    struct node* next;  
} node;

typedef struct {
    node *head;
    int length;
} linked_list;

// Prototypes
void do_demo();
linked_list *list_init();
node *create_new_node(int value);
node *insert_at_head(linked_list **list, node *node_to_insert);
node *find_node(linked_list *list, int value);
void remove_node(linked_list **list, node *node_to_remove);
void insert_after_node(linked_list *list, node *node_to_insert_after, node *newnode);
void free_list(linked_list **list);
void print_list(linked_list *list);

// Main functions
int main(void)
{
    do_demo();

    return 0;
}

void do_demo()
{
    // Instantiate lists
    linked_list *list1 = list_init();
    node *tmp;
    if (list1 == NULL) return;

    // Fill the list
    for (int i = 0; i < 10; i++)
    {
        tmp = create_new_node(i);
        insert_at_head(&list1, tmp);
    }
    print_list(list1);

    // Find a node by its value
    tmp = find_node(list1, 8);
    printf("%s\n", tmp != NULL ? "Value found." : "Value not found.");
    
    // Insert a node after the found node
    node *newNode = create_new_node(120);
    insert_after_node(list1, tmp, newNode);
    
    // Delete the found node
    remove_node(&list1, tmp);

    // Delete the list's head
    remove_node(&list1, list1->head);

    print_list(list1);
    free_list(&list1);
}

linked_list *list_init()
 {
    linked_list *list = malloc(sizeof(linked_list));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->length = 0;

    return list;
}

node *create_new_node(int value)
{
    node *newnode = malloc(sizeof *newnode);
   
    if (newnode != NULL) {
        newnode->value = value;
        newnode->next = NULL;
    };

    return newnode;
}

node *insert_at_head(linked_list **list, node *node_to_insert)
{
    node_to_insert->next = (*list)->head;
    (*list)->head = node_to_insert;
    (*list)->length++;
    return node_to_insert;
}

node *find_node(linked_list *list, int value)
{
    node *cursor = (list)->head;

    while (cursor != NULL && cursor->value != value)
        cursor = cursor->next;

    return cursor;
} 

void insert_after_node(linked_list *list, node *node_to_insert_after, node *newnode)
{
    newnode->next = node_to_insert_after->next;
    node_to_insert_after->next = newnode;
    list->length++;
}

void remove_node(linked_list **list, node *node_to_remove)
{
    // Cursor points to the list's head's address.
    node **cursor = &(*list)->head;

    // Walk through the list until the entry is found
    while ((*cursor) != node_to_remove)
        cursor = &(*cursor)->next;
    
    // Remove it
    *cursor = node_to_remove->next;
    free(node_to_remove);
    
    // Decrement list length
    (*list)->length--;
}

void free_list(linked_list **list)
{
    if (*list == NULL) return;

    int count = 0;
    node *tmp;

    while ((*list)->head != NULL)
    {
        tmp = (*list)->head;
        (*list)->head = tmp->next;
        free(tmp);
        count++;
    }

    free(*list);

    printf("%d nodes were freed.\n", count);
}

void print_list(linked_list *list)
{
    node *cursor = list->head;

    while (cursor != NULL) {
        printf("%s%d => ", (cursor == list->head) ? "(*head) " : "", cursor->value);
        cursor = cursor->next;
    }
    printf("Length = %d", list->length);
    printf("\n");
}
