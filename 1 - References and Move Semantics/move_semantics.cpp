// C++ 中的移动语义是一个有用的概念，它允许在对象之间高效、优化地转移数据的所有权。
// 移动语义的主要目标之一是提高性能，因为移动对象比深拷贝对象更快、更高效。

// 要理解移动语义，必须先理解左值 (lvalue) 和右值 (rvalue) 的概念。
// 左值的简化定义是：左值是引用内存位置的对象。
// 右值是除左值以外的任何东西。

// std::move 是将对象从一个左值移动到另一个左值的最常用方法。
// std::move 将表达式转换为右值。
// 这使我们能够像与右值一样与左值交互，并允许所有权从一个左值转移到另一个左值。

// 在下面的代码中，我们提供了一些示例，用于识别 C++ 中的表达式是左值还是右值、
// 如何使用 std::move 以及如何将右值引用传递给函数。

// 包含 std::cout (用于打印) 以进行演示。
#include <iostream>
// 包含 std::move 的实用工具头文件。
#include <utility>
// 包含 std::vector 的头文件。我们将在 containers.cpp 中更详细地介绍 vector，
// 但现在只需要知道 vector 本质上是动态数组，类型 std::vector<int> 是一个 int 数组。
// 主要的是，vector 会占用不可忽略的内存量，这里用它来展示使用 std::move 的性能优势。
#include <vector>

// 该函数接受一个右值引用作为参数。
// 它获取传入 vector 的所有权，在其末尾追加 3，并打印 vector 中的值。
void move_add_three_and_print(std::vector<int> &&vec) {
  std::vector<int> vec1 = std::move(vec);
  vec1.push_back(3);
  for (const int &item : vec1) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

// 该函数接受一个右值引用作为参数。
// 它在作为参数传入的 vector 的末尾追加 3，并打印 vector 中的值。
// 值得注意的是，它不会获取 vector 的所有权。
// 因此，传入的参数在调用者上下文中仍然可用。
void add_three_and_print(std::vector<int> &&vec) {
  vec.push_back(3);
  for (const int &item : vec) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

int main() {
  // 看这个表达式。注意 'a' 是一个左值，因为它是一个引用内存中特定空间（存储 'a' 的地方）的变量。
  // 10 是一个右值。
  int a = 10;

  // 让我们看一个将数据从一个左值移动到另一个左值的基本示例。
  // 我们在这里定义一个整数 vector。
  std::vector<int> int_array = {1, 2, 3, 4};

  // 现在，我们将这个数组的值移动到另一个左值。
  std::vector<int> stealing_ints = std::move(int_array);

  // 右值引用是引用数据本身的引用，而不是左值。
  // 对左值（例如 stealing_ints）调用 std::move 将导致表达式被转换为右值引用。
  std::vector<int> &&rvalue_stealing_ints = std::move(stealing_ints);

  // 但是，请注意，在此之后，仍然可以访问 stealing_ints 中的数据，
  // 因为拥有数据的是左值 stealing_ints，而不是 rvalue_stealing_ints。
  std::cout << "Printing from stealing_ints: " << stealing_ints[1] << std::endl;

  // 可以将右值引用传递给函数。但是，一旦右值从调用者上下文中的左值移动到被调用者上下文中的左值，
  // 它对调用者来说就实际上不可用了。本质上，在调用 move_add_three_and_print 之后，
  // 我们不能使用 int_array2 中的数据。它不再属于 int_array2 左值。
  std::vector<int> int_array2 = {1, 2, 3, 4};
  std::cout << "Calling move_add_three_and_print...\n";
  move_add_three_and_print(std::move(int_array2));

  // 在这里尝试对 int_array2 做任何事情都是不明智的。取消注释下面的代码来试试看！
  //（在我的机器上，这会导致段错误...）注意：这可能在你的机器上能正常工作。
  // 但这并不意味着这样做是明智的！
  // std::cout << int_array2[1] << std::endl;

  // 如果我们不将被调用者上下文中的左值移动到被调用者上下文中的任何左值，
  // 那么函数实际上会将传入的右值引用视为一个引用，
  // 并且此上下文中的左值仍然拥有 vector 数据。
  std::vector<int> int_array3 = {1, 2, 3, 4};
  std::cout << "Calling add_three_and_print...\n";
  add_three_and_print(std::move(int_array3));

  // 正如这里所见，我们可以从这个数组中打印。
  std::cout << "Printing from int_array3: " << int_array3[1] << std::endl;

  return 0;
}