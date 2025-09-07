// 包含 std::cout（用于打印）以进行演示。
#include <iostream>
// 包含 std::set 库。
#include <set>
// 包含 C++ 字符串库。
#include <string>
// 包含 std::vector 库。
#include <vector>
// 包含 std::unordered map 库。
#include <unordered_map>

// C++ auto 关键字是一个告诉编译器通过其初始化表达式推断声明变量类型的关键字。
// 它可能非常有用，因为它提高了开发者的效率
//（开发者不再需要输入冗长、复杂的类型名称）。
// 它在 for-each 循环的上下文中也很有用。
// 然而，使用 auto 存在风险，开发者可能不知道他们正在使用的类型，
// 因此存在编写有错误和不起作用的代码的风险。
// 所以要小心！

// 具有非常长名称的基本模板类，用来展示 auto 的有用性。
template <typename T, typename U> class Abcdefghijklmnopqrstuvwxyz {
public:
  Abcdefghijklmnopqrstuvwxyz(T instance1, U instance2)
      : instance1_(instance1), instance2_(instance2) {}

  void print() const {
    std::cout << "(" << instance1_ << "," << instance2_ << ")\n";
  }

private:
  T instance1_;
  U instance2_;
};

// 返回具有非常长名称的这个类的对象的模板函数。
template <typename T>
Abcdefghijklmnopqrstuvwxyz<T, T> construct_obj(T instance) {
  return Abcdefghijklmnopqrstuvwxyz<T, T>(instance, instance);
}

int main() {
  // auto 关键字用于初始化变量 a。
  // 在这里，类型被推断为 int 类型。
  auto a = 1;

  // 这里是更多使用 auto 声明基本变量的例子。
  // 根据所使用的 IDE，它可能会显示 a、b 和 c 的类型。
  auto b = 3.2;
  auto c = std::string("Hello");

  // auto 对于这些之前的例子并不是特别有用。
  // 如你所见，
  // 输入 int a = 1;、float b = 3.2; 和 std::string c = "Hello";
  // 不会产生显著的开销。
  // 然而，肯定会有类型名称冗长复杂的情况，
  // 或者当类型名称大量使用模板时，
  // 使用 auto 可能会很有帮助。
  Abcdefghijklmnopqrstuvwxyz<int, int> obj = construct_obj<int>(2);
  auto obj1 = construct_obj<int>(2);

  // 也许对于一行代码来说，这看起来并不那么方便，但想象一下
  // 如果在代码中长时间使用一个名称很长的类是有用的。
  // 那么，我想这会节省很多输入时间！

  // 关于 auto 关键字需要注意的一个重要事情是它默认复制对象，
  // 这可能会降低性能。
  // 看下面的例子，我们构造一个 int 向量，
  // 并想定义一个对它的引用变量。
  std::vector<int> int_values = {1, 2, 3, 4};

  // 以下代码将 int_values 深拷贝到 copy_int_values 中，
  // 因为 auto 推断类型为 std::vector<int>，
  // 而不是 std::vector<int>&。
  auto copy_int_values = int_values;

  // 然而，以下代码定义了 ref_int_values，
  // 它是对 int_values 的引用，
  // 因此不会深拷贝 int_values 向量。
  auto& ref_int_values = int_values;

  // auto 关键字对于遍历 C++ 容器也很有用。
  // 例如，让我们构造一个具有 std::string 键和 int 值的无序映射，
  // 并讨论遍历它的方法。
  std::unordered_map<std::string, int> map;
  map.insert({{"andy", 445}, {"jignesh", 645}});

  // unordered_map.cpp 中提到的一种方法是
  // 使用带有迭代器的 for 循环来遍历映射。
  // 比较下面两个循环的可读性。
  std::cout << "Printing elements in map...\n";
  for (std::unordered_map<std::string, int>::iterator it = map.begin();
       it != map.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")"
              << " ";
  }
  std::cout << std::endl;

  std::cout << "Printing elements in map with auto...\n";
  for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")"
              << " ";
  }
  std::cout << std::endl;

  // 也可以使用 auto 关键字来遍历向量和集合。
  std::vector<int> vec = {1, 2, 3, 4};
  std::cout << "Printing elements in vector with auto...\n";
  for (const auto& elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::set<int> set;
  for (int i = 1; i <= 10; ++i) {
    set.insert(i);
  }

  std::cout << "Printing elements in set with auto...\n";
  for (const auto &elem : set) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  // 总的来说，auto 是一个有用的 C++ 关键字，可以用来更高效地编写代码，
  // 并编写更干净、更可读的代码。
  // 请记住，使用 auto 来遍历 C++ 容器在实践中更好，
  // 因为它产生更可读的代码。
  // 然而，如果你不确定正在使用的类型，
  // 总是可以回到自己弄清楚类型的方法。

  return 0;
}