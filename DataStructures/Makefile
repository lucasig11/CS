# Compiler
CC=gcc
 
# Flags for compiler
CC_FLAGS=-W -Wall -pedantic

all: lists hash tree

lists : singly doubly

singly: LinkedList/singly_linked_list.c 
	$(CC) -o LinkedList/singly_linked_list LinkedList/singly_linked_list.c $(CC_FLAGS)

doubly: LinkedList/doubly_linked_list.c
	$(CC) -o LinkedList/doubly_linked_list LinkedList/doubly_linked_list.c $(CC_FLAGS)

hash: HashTable/hashtable.c
	$(CC) -o HashTable/hashtable HashTable/hashtable.c $(CC_FLAGS)

tree: Trees/tree.c
	$(CC) -o Trees/tree Trees/tree.c $(CC_FLAGS)
