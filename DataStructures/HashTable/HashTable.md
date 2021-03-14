## Hash tables

- The table inputs are *hashed*, and this hash maps to a location (index) in the table where our item will be inserted.
- Collisions can be dealt with using different strategies:
  - **Open adressing:**
    - Looks for the next available space in the table, through re-hashing or just *linear probing*.
  - **External chaining:**
    - If the place we're trying to insert is already occupied then the colliding items are chained in a *linked list*.
- **Hash function:** 
  - Must produce the same output for the same input.
  - Should be as "random" as possible.
  - Should be fast.
- Finding data in arrays and linked lists (Linear time, *O(n)*) is assimptotically more complex than finding in a hash table (Constant time, *O(1)*).

**[See hash table implementation in C.](hashtable.c)**

~~~bash
cd DataStructures
make all                 
./demo/hashtable 
~~~
