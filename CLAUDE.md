# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

```bash
mkdir -p build && cd build && cmake .. && make -j$(sysctl -n hw.ncpu)
```

All executables are output to the `build/` directory. Each `.cpp` file compiles to an executable matching its basename (e.g., `references.cpp` → `references`).

## Project structure

This is a C++ modern features bootcamp derived from CMU 15-445's bootcamp. Each chapter directory contains standalone, self-contained `.cpp` files — there are no shared headers or libraries between them.

- **1 - References and Move Semantics**: lvalue/rvalue references, `std::move`, move constructors/assignment
- **2 - C++ Templates**: templated functions and classes
- **3 - Misc**: wrapper classes, iterators, namespaces
- **4 - Containers**: `std::vector`, `std::set`, `std::unordered_map`, `auto`
- **5 - Memory**: `std::unique_ptr`, `std::shared_ptr`
- **6 - Synch Primitives**: `std::mutex`, `std::scoped_lock`, `std::condition_variable`, `std::shared_mutex` (rwlock)
- **spring2024/**: custom smart pointer implementation (`s24_my_ptr.cpp`)
- **notes/**: Chinese-language markdown notes corresponding to each code file

## Conventions

- C++17 standard, clang-14 recommended (Apple Clang also works)
- Each `.cpp` file is a self-contained tutorial/demo — they are meant to be read and studied, not used as a library
- The CMakeLists.txt explicitly lists each source file; adding a new `.cpp` requires adding a corresponding `add_executable` line
