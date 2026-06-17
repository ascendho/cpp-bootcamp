## Smart Pointers I — unique_ptr

- `unique_ptr` is a smart pointer with exclusive ownership. Its characteristics include automatic management of dynamically allocated memory, ensuring only one owner per object, automatic memory release at end of scope, and zero-overhead abstraction (virtually no performance penalty).
- `unique_ptr`'s copy constructor is implicitly deleted (`= delete`), so it does not support copy semantics, but it does support move semantics.
- If a function only temporarily uses the object, pass by reference (`std::unique_ptr<T> &`). If the function needs to take ownership, use move semantics (`std::move(ptr)`).
- `make_unique` is used to create `unique_ptr` objects and is the recommended approach over direct construction.
