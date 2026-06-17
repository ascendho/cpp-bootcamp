## Sets

- Most standard library implementations (such as GCC's libstdc++ and Microsoft's MSVC library) use **red-black trees** as the underlying data structure for `std::set`.
- `std::set` chooses red-black trees as its underlying implementation because it offers the best balance between **lookup efficiency**, **insertion/deletion performance**, **memory usage**, and **implementation complexity**.
- Because the underlying implementation uses a red-black tree (a balanced binary search tree), `std::set` is an ordered set — elements are automatically kept in order upon insertion, and an in-order traversal naturally produces a sorted sequence.
- Default ordering is ascending; custom sort order can be specified via a comparison function.
