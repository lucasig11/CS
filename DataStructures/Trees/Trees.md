## Tree

- Tree is an abstract data type, hierarchically organized with linked nodes.
- In a *binary tree* (other than in a *generic tree*), each node may have up to 2 children (left and right).
- **Binary search tree (BST):**
  - Or *sorted/ordered binary tree*.
  - Is a *rooted* binary tree at which the parent node key is greater than its left child's key and less than it's right child's key.

![Binary Tree Example](binary-tree.png)

**[See binary search tree implementation in C.](tree.c)**

~~~bash
cd DataStructures       
make all                    
./demo/tree
~~~