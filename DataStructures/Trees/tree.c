#include <stdio.h>
#include <stdlib.h>

// This is the indentation when printing the tree
#define COUNT 7

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

// Initialize root
node *root = NULL;

int main(void)
{
    insert_node(&root, 15); // new root;
    insert_node(&root, 19);
    insert_node(&root, 24); 
    insert_node(&root, 13); 
    insert_node(&root, 16);
    insert_node(&root, 9);
    insert_node(&root, 11);
    insert_node(&root, 21);
    insert_node(&root, 14);
    insert_node(&root, 5);
    
    printf("\n-------------New tree------------\n");
    print_tree(root);

    node *find = find_node(root, 16);
    if (find != NULL) {
        printf("\n----------Binary Search----------\n\n");
        printf("Value found: %d\n", find->value);
    }

    printf("\n----------Inverting tree----------\n");
    invert_tree(root);
    print_tree(root);

    unload_tree(&root);    
    printf("\n\n");
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
