# Compiler
CC=gcc
 
# Flags for compiler
CC_FLAGS=-W -Wall -pedantic

all: lists hash tree

lists : singly doubly

singly: dir LinkedList/singly_linked_list.c
	$(CC) -o demo/singly_linked_list LinkedList/singly_linked_list.c $(CC_FLAGS)

doubly: dir LinkedList/doubly_linked_list.c
	$(CC) -o demo/doubly_linked_list LinkedList/doubly_linked_list.c $(CC_FLAGS)

hash: dir HashTable/hashtable.c
	$(CC) -o demo/hashtable HashTable/hashtable.c $(CC_FLAGS)

tree: dir Trees/tree.c
	$(CC) -o demo/tree Trees/tree.c $(CC_FLAGS)

dir:
	mkdir -p demo

clear:
	$(RM) -R demo
