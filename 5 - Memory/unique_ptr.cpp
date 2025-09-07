// 智能指针是一种用于内存管理（有时还有其他功能）的数据结构类型，
// 用于没有内置内存管理的语言（例如 C++）。
// 具有内置内存管理的语言示例是任何具有垃圾收集的语言，如 Java 或 Python。
// 现代 C++ 标准库的两个智能指针（也是你在课堂上将使用的）
// 是 std::unique_ptr 和 std::shared_ptr。
// std::unique_ptr 和 std::shared_ptr 都自动处理内存分配和释放，
// 并在底层包含原始指针。
// 换句话说，它们是原始指针的包装类。
// 在这个文件中，我们将讨论 std::unique_ptr。
// std::unique_ptr 是一种保持对象独占所有权的智能指针类型。
// 这意味着没有两个 std::unique_ptr 实例可以管理同一个对象。

// 包含 std::cout（用于打印）以进行演示。
#include <iostream>
// 包含 std::unique_ptr 功能。
#include <memory>
// 字符串库，用于演示打印帮助。
#include <string>
// 包含 utility 头文件以使用 std::move。
#include <utility>

// 基本点类。（稍后会使用）
class Point {
public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}
  inline int GetX() { return x_; }
  inline int GetY() { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }

private:
  int x_;
  int y_;
};

// 接受唯一指针引用并将其 x 值更改为 445 的函数。
void SetXTo445(std::unique_ptr<Point> &ptr) { ptr->SetX(445); }

int main() {
  // 这是如何初始化类型为 std::unique_ptr<Point> 的空唯一指针。
  std::unique_ptr<Point> u1;
  // 这是如何使用默认构造函数初始化唯一指针。
  std::unique_ptr<Point> u2 = std::make_unique<Point>();
  // 这是如何使用自定义构造函数初始化唯一指针。
  std::unique_ptr<Point> u3 = std::make_unique<Point>(2, 3);

  // 在这里，对于 std::unique_ptr 实例 u，
  // 我们使用语句 (u ? "not empty" : "empty")来确定指针 u 是否包含托管数据。
  // 主要要点是 std::unique_ptr 类在其对象上有一个到布尔类型的转换函数，
  // 因此每当我们将 std::unique_ptr 视为布尔值时，就会调用此函数。
  // 例如，这可以在以下示例中使用。
  if (u1) {
    // 这不会打印，因为 u1 是空的。
    std::cout << "u1's value of x is " << u1->GetX() << std::endl;
  }

  if (u2) {
    // 这将打印，因为 u2 不是空的，并且包含一个托管的 Point 实例。
    std::cout << "u2's value of x is " << u2->GetX() << std::endl;
  }

  // 注意 u1 是空的，而 u2 和 u3 不是空的，因为它们是用 Point 实例初始化的。
  std::cout << "Pointer u1 is " << (u1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u2 is " << (u2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;

  // 由于 std::unique_ptr 的实例只能有一个所有者，
  // 它没有拷贝构造函数。
  // 因此，这段代码不会编译。取消注释来尝试！
  // std::unique_ptr<Point> u4 = u3;

  // 然而，可以通过 std::move 转移唯一指针的所有权。
  std::unique_ptr<Point> u4 = std::move(u3);

  // 注意，因为 u3 是一个左值，它不再包含任何托管对象。
  // 它是一个空的唯一指针。让我们重新测试空性。
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u4 is " << (u4 ? "not empty" : "empty") << std::endl;

  // 最后，让我们讨论如何将 std::unique_ptr 实例作为参数传递给函数。
  // 主要是，你应该将其作为引用传递，这样所有权不会改变。
  // 你可以在函数 SetXTo445（此文件的第 44 行）中看到这个例子。
  SetXTo445(u4);

  // 现在，让我们打印 u4 的 x 值来确认更改发生了，
  // 但 Point 实例的所有权已保留给 u4。
  std::cout << "Pointer u4's x value is " << u4->GetX() << std::endl;

  return 0;
}