## Wrapper Classes

- A wrapper class is a design pattern used to encapsulate and manage resources (memory, files, network connections, etc.). It acts as a "wrapper" or "manager" between the resource and the rest of the program.
- Wrapper classes typically disable copying to prevent multiple objects from managing the same resource, and support move semantics to transfer resource ownership.
- `std::unique_ptr<T>`, `std::shared_ptr<T>`, `std::lock_guard<Mutex>`, and `std::fstream` are examples of wrapper classes in the C++ standard library.
- RAII (Resource Acquisition Is Initialization) is a C++ programming technique whose core idea is binding resource lifetimes to object lifetimes, achieving automatic, safe, and efficient resource management.
- The `const` keyword indicates a const member function that does not modify the object's state — it promises not to change any member variables and is a read-only operation. The `this` pointer's type is `const IntPtrManager*`. For example:

```cpp
    // Getter function.
    int GetVal() const {
      return *ptr_;
    }
```

- Analyzing this code:

```cpp
    // Move assignment operator for this wrapper class. Similar techniques as
    // the move constructor.
    IntPtrManager &operator=(IntPtrManager &&other) {
      if (ptr_ == other.ptr_) {
        return *this;
      }
      if (ptr_) {
        delete ptr_;
      }
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
      return *this;
    }
```

First, a self-assignment check is performed — uncommon but technically possible. Then the current resource is released to prevent memory leaks. Finally, the source object's resource is transferred to the current object, and the source is invalidated to prevent double deletion.
