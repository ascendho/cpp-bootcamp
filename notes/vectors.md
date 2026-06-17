## Vectors

- The `inline` keyword primarily suggests that the compiler perform inline optimization — expanding the function code directly at the call site instead of performing a function call, eliminating call overhead (stack push, jump, return, etc.). It also allows functions to be defined in header files, solving the multiple-definition problem.
- `inline` is suitable for frequently called, short functions or performance-sensitive scenarios.
- The `const` keyword on a function promises not to modify the object's state, and the compiler verifies that no members are indeed modified.
- `const` objects can only call `const` member functions.
- Analyzing this code:

```cpp
void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}
```

1. Pass-by-reference instead of pass-by-value in the function parameter: if the vector has a large capacity, copying would be expensive.
2. The reference in the loop offers little performance benefit here since `int` is only 4 bytes and copying is cheap — modern compilers typically optimize away the difference. However, if `vec` were a vector of `string`, there would be a meaningful performance gain.
3. The `const` keyword in the loop ensures the function does not accidentally modify the original `vec` elements.

- `push_back` copies or moves an already-constructed object to the end of the container. It accepts object copies or rvalue references and is suitable when an existing object needs to be moved or when the original object must be preserved.
- `emplace_back` constructs the object in-place directly at the end of the container. It accepts constructor arguments and is suitable for complex objects or performance-sensitive scenarios.
- Lambda expressions are an important modern C++ feature, allowing us to define anonymous functions inline. For example:

```cpp
 point_vector.erase(
      std::remove_if(point_vector.begin(), point_vector.end(),
                     [](const Point &point) { return point.GetX() == 37; }),
      point_vector.end());
```

Here `[]` is the capture list (empty means no external variables are captured), `(const Point &point)` is the parameter list accepting a const Point reference, and `{ return point.GetX() == 37; }` is the function body returning a bool.

- `remove_if` works by scanning elements and moving those that don't satisfy the condition to the front, and those that do to the back, returning a partition iterator `new_end` (pointing to the "new logical end").
- `erase` deletes all elements from `new_end` to `end`.
- The erase-remove idiom is more efficient than naive deletion because it reduces the number of element moves.
- C++20 provides `std::erase_if` to simplify the above operation.
