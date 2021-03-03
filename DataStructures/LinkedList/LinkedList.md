## Linked List


- Data is noncontiguously structured in nodes, every which contain the data itself and a pointer to the next node's address and, if it's a *doubly-linked list*, a pointer to the previous node's address.
- Can be asymptotically less complex to manipulate insertions than other data structures, like in a contiguous array.
- A *doubly linked list* makes the deletion process faster, since you're able to delete a node by directly accessing him (O(1)) without taking the risk of losing the edges that pointed to him. 

**[See singly-linked list implementation in C.](singly_linked_list.c)**  

**[See doubly-linked list implementation in C.](doubly_linked_list.c)**

~~~bash
cd DataStructures       
make lists                    
cd LinkedList
./singly_linked_list    ## or ./doubly_linked_list
~~~
