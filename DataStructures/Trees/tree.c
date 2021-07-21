#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>

// This is the indentation when printing the tree
#define COUNT 7
#define TREE_SIZE 2000000
 
// Undefine any definitions
#undef calculate
#undef getrusage

// Node definition
typedef struct node {
    int value;
    struct node *left, *right;
} node;

// Prototypes
node *create_node(int value);
void invert_tree(node *root);
void unload_tree(node **root);
node *insert_node(node **root, int value);
node *find_node(node *root, int value);
void Rprint_tree(node *root, int space);
void print_tree(node *root);
double calculate(const struct rusage *b, const struct rusage *a);

// Initialize root
node *root = NULL;

int main(void)
{
    // Structures for timing data
    struct rusage before, after;
    double time_insert = 0.0, time_search = 0.0, time_invert = 0.0, time_unload = 0.0;

    // Seed random number
    srand(time(NULL));
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < TREE_SIZE; i++)
    {
        int r = rand() % TREE_SIZE;
        insert_node(&root, r);
    }
    insert_node(&root, 16);
    getrusage(RUSAGE_SELF, &after);
    
    // Calculate time to load dictionary
    time_insert = calculate(&before, &after);

    printf("\n-------------New tree------------\n");
    // print_tree(root);

    getrusage(RUSAGE_SELF, &before);
    node *find = find_node(root, 16);
    getrusage(RUSAGE_SELF, &after);

    time_search = calculate(&before, &after);

    if (find != NULL) {
        printf("\n----------Binary Search----------\n\n");
        printf("Value found: %d\n", find->value);
    }

    printf("\n----------Inverting tree----------\n");
    getrusage(RUSAGE_SELF, &before);
    invert_tree(root);
    getrusage(RUSAGE_SELF, &after);
    time_invert = calculate(&before, &after);
    // print_tree(root);

    getrusage(RUSAGE_SELF, &before);
    unload_tree(&root);    
    getrusage(RUSAGE_SELF, &after);
    time_unload = calculate(&before, &after);

    printf("\n\n");

    printf("TIME IN insert:         %.6fs\n", time_insert);
    printf("TIME IN search:         %.6fs\n", time_search);
    printf("TIME IN invert:         %.6fs\n", time_invert);
    printf("TIME IN unload:         %.6fs\n", time_unload);
    printf("TIME IN TOTAL:         %.6fs\n", 
            time_unload + time_insert + time_search + time_invert);

    return 0;
}

// Creates new 'loose' node
node *create_node(int value)
{
    // Allocate a new node on the heap
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) return NULL;
    
    // Set initial pointers
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    
    return new_node;
}

// Creates & inserts a new node into the tree
node *insert_node(node **root, int value)
{
    if (*root == NULL)
    {
        (*root) = create_node(value);
        return (*root);
    }
    // the left node is smaller. 
    // the right node is larger.
    if ((*root)->value > value) return insert_node(&(*root)->left, value);
    if ((*root)->value < value) return insert_node(&(*root)->right, value);
    return NULL;
}

// Finds a node with the corresponding value
node *find_node(node *root, int value)
{
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    if (root->value > value) return find_node(root->left, value);
    return find_node(root->right, value);
}

// Inverts the tree
void invert_tree(node *root)
{
    if (root == NULL) return;

    // Base case: there's nothing to invert (node has no child);
    if (root->left == NULL && root->right == NULL) return;
    
    // Move to the children
    invert_tree(root->left);
    invert_tree(root->right);

    // Swap the node's children
    node *tmp   = root->left;
    root->left  = root->right;
    root->right = tmp; 

    return;
}

// Unloads tree from the heap
void unload_tree(node **root)
{
    if (*root == NULL) return;
    if ((*root)->left != NULL || (*root)->right != NULL) 
    {
        unload_tree(&(*root)->left);
        unload_tree(&(*root)->right);
        unload_tree(&(*root));
        return;
    }
    free(*root);
    *root = NULL;
    return;
}

// Recursion helper
void Rprint_tree(node *root, int space) 
{ 
    // Base case 
    if (root == NULL) return;

    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    Rprint_tree(root->right, space); 
  
    // Print current node after space count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d -<\n", root->value); 
  
    // Process left child 
    Rprint_tree(root->left, space); 
}

// Calls the recursive print_tree
void print_tree(node *root)
{
    if (root == NULL) {
        printf(">--[Tree is empty]--<\n");
        return; 
    }
    Rprint_tree(root, 0);
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}