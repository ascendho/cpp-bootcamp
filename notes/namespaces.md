## Namespaces

- Namespaces are a mechanism in C++ for organizing code and avoiding naming conflicts. Their main purposes include providing scope, organizing code, and preventing name collisions.
- C++ supports nested namespace definitions. Use the `::` operator to access identifiers in different namespaces.
- The `using` keyword simplifies namespace usage by bringing a namespace or specific identifier into the current scope.
- Avoid `using namespace` in header files, as it affects all code that includes that header. Also avoid `using namespace` in global scope, as it easily causes naming conflicts.
- Best practice: use specific `using` declarations in source files, or use `using namespace` within function scope:

  ```cpp
  // 1. Use specific using declarations in source files
  using std::cout;
  using std::endl;
  using std::vector;

  // 2. Or use using namespace within function scope
  void function() {
      using namespace std;
      cout << "Safe to use here" << endl;
  }
  ```
