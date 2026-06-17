## Move Semantics

- `std::move` itself does nothing — it is merely a type cast that tells the compiler to treat an lvalue as an rvalue. The actual "moving" of data is performed by the move constructor.
- An rvalue reference is fundamentally just a reference — it points to the same memory. Modifying one will affect the other.
- Rvalue references are primarily used for function parameters (e.g., function overloading), signaling to the compiler that "this object can be safely moved" (the key advantage over ordinary references).
- Move semantics is essentially pointer swapping, not data copying.
- While lvalue reference parameters can also achieve move semantics, rvalue reference parameters express intent more clearly (like a "contract"), explicitly telling the caller that the function will consume/transfer the original data, providing greater safety.
