## Iterators

- An iterator is a design pattern and programming concept that provides a uniform way to access elements in a container (arrays, linked lists, trees, etc.) without exposing the container's internal structure.
- The core value of iterators lies in abstraction, uniformity, flexibility, safety, and composability.
- Analyzing this code:

```cpp
for (DLLIterator iter = dll.Begin(); iter != dll.End(); ++iter) {
    std::cout << *iter << " ";
}
```

1. `dll.Begin()` returns not a pointer, but a newly constructed `DLLIterator` object that internally holds a pointer to the first node.
2. `dll.End()` returns an iterator representing "past-the-end" (`curr_` = `nullptr`). This is called on every loop condition check, incurring temporary object overhead.
3. The condition compares the iterator's `curr_` pointer against `nullptr` to determine if the end of the list has been reached.
4. Prefix `++iter` is recommended because it avoids creating a temporary object and is more efficient. Postfix `++` creates a temporary object each time, with extra construction/destruction overhead.
5. Best practice: prefer prefix `++iter` in for loops unless you explicitly need postfix `++` semantics (i.e., using the value before increment).

- `size_t` is an unsigned integer type in C++ (0 and positive integers), specifically designed to represent object sizes and array indices, avoiding safety issues from negative indices.
- `size_t` is 8 bytes on 64-bit systems and 4 bytes on 32-bit systems, providing portability.
