## Hash Maps

- `unordered_map` is essentially a **hash table**, using buckets and linked lists to handle collisions. It provides constant-time lookup performance in most cases, at the cost of higher memory overhead and unordered elements.
- The traversal order of `unordered_map` is unpredictable, influenced by the hash function, bucket array size, and the order of elements within buckets.
- The trade-off for being unordered is faster lookup speed, since the storage location can be computed directly via the hash function without needing multiple key comparisons as in a tree.
