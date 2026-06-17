## Move Constructors

- The `&` in `Person &operator=(Person &&other)` indicates a return-by-reference, not a pointer. This avoids unnecessary copies, supports chained assignment, and is more performant.
- `this` is a pointer to the current object, implicitly present in every non-static member function.
- `*this` dereferences the `this` pointer, yielding the current object itself.
- For fundamental types (integers, floats, characters, booleans, raw pointers, etc.), the compiler builds a symbol table at compile time mapping variable names to memory locations. During code generation, variable names are replaced with concrete memory access instructions — **variable names disappear after compilation**. The compiler handles this "translation" via the symbol table.
- Fundamental types have no concept of "moving" because they lack move constructors or move assignment operators. `std::move` merely casts them to rvalue references, and ordinary assignment is ultimately invoked. For example:

```cpp
b = a;              // direct assignment
b = std::move(a);   // "move" assignment
```

The compiler may optimize both to identical instruction sequences — the underlying operation is still a memory copy.

- **Core principle**: use move semantics only for objects with complex resource management and high copy costs (strings, containers, smart pointers, custom class objects). For fundamental types, direct copying is fine.
- `= delete` explicitly tells the compiler not to generate certain functions — a way to actively disable specific operations.
- When `= delete` is used to disable the copy constructor and copy assignment operator, the design intent is to enforce move semantics, avoid expensive deep copies, and ensure resources can only be moved, not copied.
