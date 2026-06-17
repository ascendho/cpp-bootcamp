## Templated Functions

- `template <>` indicates template specialization, providing a dedicated implementation for a specific type. For example:

```cpp
template <typename T> void print_msg() { std::cout << "Hello world!\n"; }

// Specialized templated function, specialized on the float type.
template <> void print_msg<float>() {
  std::cout << "print_msg called with float type!\n";
}
```

The specialized version overrides the generic version. This is commonly used when certain types require special handling.

- Non-type template parameters, for example:

```cpp
// Lastly, template parameters do not have to be classes. Take this basic (yet
// very contrived) function that takes in a bool as a template parameter and
// does different things to the argument depending on the boolean argument.
template <bool T> int add3(int a) {
  if (T) {
    return a + 3;
  }

  return a;
}
```

The key benefits of this design are:

1. Computation and optimization happen at compile time, avoiding runtime overhead
2. The type system guarantees constant correctness, avoiding magic numbers

The core programming philosophy is: **shift runtime decisions to compile time** for better performance. This is especially important in systems programming (databases, operating systems, game engines, etc. — domains where performance is critical).

- In modern C++, `constexpr if` is recommended for similar functionality, as it offers clearer syntax and intent.
