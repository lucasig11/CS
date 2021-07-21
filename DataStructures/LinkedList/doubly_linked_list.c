#include <stdio.h>
#include <stdlib.h>

// Type definition
typedef struct node {
    int value;
    struct node* next; 
    struct node* prev; 
} node;

typedef struct {
    node *head;
    int length;
} linked_list;

// Prototypes
linked_list *list_init();
node *node_create(int value);
node *list_searchNode(linked_list *list, int value);
node *list_headInsert(linked_list **list, node *new_node);
void list_removeNode(linked_list **list, node *node_to_remove);
void list_insertAfterNode(node *node_to_insert_after, node *new_node);
void list_free(linked_list **list);
void print_list(linked_list *list);
void do_demo();

int main()
{
    do_demo(); 
    return 0;
}

void do_demo()
{
    // Initialize pointers in the stack to empty lists on the heap
    linked_list *list1 = list_init(), *list2 = list_init();
    if (list1 == NULL || list2 == NULL) return;
    
    node *tmp;

    printf("Creating lists...\n");
    // Fill the 1st list
    for (int i = 0; i < 14; i++)
    {
        tmp = node_create(i);
        list_headInsert(&list1, tmp);
    }
    printf("List 1:\n");
    print_list(list1);
    printf("\n");

    // Fill the 2nd list
    for (int i = 7; i >= 0; i--)
    {
        tmp = node_create(i);
        list_headInsert(&list2, tmp);
    }
    printf("List 2:\n");
    print_list(list2);
    printf("\n");

    // Find a node by it's value
    printf("Searching for a node in the list with the value 12... ");
    tmp = list_searchNode(list1, 12);
    printf("%s\n", tmp != NULL ? "Node found!" : "Node not found!");
    printf("\n");

    // Remove the found node
    printf("Delete the found node:\n");
    list_removeNode(&list1, tmp);
    print_list(list1);
    printf("\n");
    
    // Remove list's head
    printf("Delete the list's head:\n");
    list_removeNode(&list2, list2->head);
    print_list(list2);
    printf("\n");
    
    // Clear the heap
    printf("Clearing the heap... \n");
    list_free(&list1);
    list_free(&list2);
    printf("\n");
}

node *node_create(int value)
{
    node *new_node = malloc(sizeof *new_node);
    if (new_node != NULL) {
        // Set the node values
        new_node->value = value;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
}

linked_list *list_init() {
    linked_list *list = malloc(sizeof(linked_list));
    if (list != NULL) {
        list->head = NULL;
        list->length = 0;
    }
    return list;
}

node *list_headInsert(linked_list **list, node *new_node)
{
    // Insert new node in front of head
    new_node->next = (*list)->head;

    if (new_node->next != NULL)
        new_node->next->prev = new_node;

    // Set the new node as head
    (*list)->head = new_node;

    // Increment list length variable
    (*list)->length++;

    return new_node;
}

node *list_searchNode(linked_list *list, int value)
{
    node *tmp = list->head;

    while (tmp->value != value ) 
        tmp = tmp->next;

    return tmp;
} 

void list_insertAfterNode(node *node_to_insert_after, node *new_node)
{
    new_node->next = node_to_insert_after->next;

    if (new_node->next != NULL)
        new_node->next->prev = new_node;

    new_node->prev = node_to_insert_after;
    node_to_insert_after->next = new_node;
}

void list_removeNode(linked_list **list, node *node_to_remove)
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

void list_free(linked_list **list)
{
    int count = 0;
    node *tmp;

    // Walk the list, freeing the nodes
    while ((*list)->head != NULL)
    {
        tmp = (*list)->head;
        // Change the list's head
        (*list)->head = tmp->next;
        // Free old head
        free(tmp);
        count++; 
    }

    // Free the list
    free(*list);
    printf("%d nodes were freed.\n", count);
}

void print_list(linked_list *list)
{
    if (list == NULL) return;

    node *tmp = list->head;
    while (tmp != NULL)
    {
        printf("%s %d <=> ", tmp == list->head ? "(*head) " : "", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
    printf("The list has %d nodes\n", list->length);
}
