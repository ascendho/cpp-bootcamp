## Smart Pointers II — shared_ptr

- `shared_ptr` is a smart pointer with shared ownership, allowing multiple pointer instances to jointly own and manage the same object. It supports reference counting and automatic memory management.
- The key difference between ordinary references and rvalue references is that the latter "hints" that resources may be "stolen" (though no actual move occurs in this program). Summary:

| Feature              | Ordinary Reference (&) | Rvalue Reference (&&)                        |
| -------------------- | ---------------------- | -------------------------------------------- |
| **Accepts**          | Lvalues (variables)    | Rvalues (temporaries, std::move results)     |
| **Call syntax**      | `func(var)`            | `func(std::move(var))` or `func(temp_obj)`   |
| **Reference count**  | Unchanged              | Unchanged                                    |
| **Semantic meaning** | Borrowed use           | Preparing to transfer ownership              |
| **Source state**     | Unchanged              | May be "moved from" (depends on impl)        |

- `make_shared` is a template function for creating `shared_ptr`. Compared to the traditional approach (`std::shared_ptr<int> ptr(new int(42));`), it is more memory-efficient and exception-safe. Summary:

| Feature              | make_shared           | shared_ptr(new T) |
| -------------------- | --------------------- | ----------------- |
| **Memory efficiency** | High (single alloc)  | Low (two allocs)  |
| **Exception safety** | Yes                   | Potentially unsafe |
| **Code brevity**     | Yes                   | More verbose      |
| **Custom deleter**   | Not supported         | Supported         |
| **Memory release**   | May be delayed        | Timely            |

- Differences between `shared_ptr`, `unique_ptr`, and `weak_ptr`:

| Feature            | shared_ptr  | unique_ptr  | weak_ptr       |
| ------------------ | ----------- | ----------- | -------------- |
| **Ownership**      | Shared      | Exclusive   | Non-owning     |
| **Copyable**       | Yes         | No          | Yes            |
| **Reference count**| Yes         | No          | Does not increment |
| **Performance**    | Higher      | Very low    | Low            |
