# Contributing

Thanks for your interest in contributing! This project is a C++ modern features bootcamp derived from CMU's 15-445 course, aimed at helping developers learn modern C++ through translated and annotated examples.

## Ways to Contribute

- **Fix errors**: If you find a bug in the code or a mistake in the notes, please open an issue or PR.
- **Improve translations**: Help refine the Chinese translations of code comments and notes.
- **Add new content**: New chapters covering additional C++ features are welcome.
- **English notes**: Help translate the Chinese notes (`notes/`) into English to broaden the audience.

## Development Setup

```bash
mkdir build && cd build && cmake .. && make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu)
```

Each `.cpp` file compiles to a standalone executable. Add new source files by appending an `add_executable` line to `CMakeLists.txt`.

## Pull Request Guidelines

1. Keep PRs focused — one topic per PR.
2. Ensure the project builds with `cmake --build build` before submitting.
3. Follow the existing code style (2-space indentation, Chinese comments in source files).
