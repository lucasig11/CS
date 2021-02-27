#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next; 
}node; 

void print_list(node *head);

int main(void)
{
    node n1, n2, n3;
    node *head;

    // Set node values
    n1.value = 13,
    n2.value = 14,
    n3.value = 15,

    // Link the nodes
    head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = NULL;

    print_list(head);   
    return 0;
}

void print_list(node *head)
{
    node *tmp = head;

    while (tmp != NULL) {
        printf("%d - ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}
