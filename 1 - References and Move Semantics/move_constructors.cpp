// 移动构造函数和移动赋值运算符是在类内部实现的方法，用于有效地将资源从一个对象移动到另一个对象，
// 通常使用 std::move。
// 这些类方法接受另一个相同类型的对象，并将其资源移动到调用该方法的实例中。
// 在此文件中，我们将探索如何实现和使用移动构造函数和移动赋值运算符。

// 包含 std::cout (用于打印) 以进行演示。
#include <iostream>
// 包含 std::move 的实用工具头文件。
#include <utility>
// 包含 C++ 字符串库。
#include <string>
// 包含 uint32_t 的头文件。
#include <cstdint>
// 包含 std::vector 的头文件。我们将在 containers.cpp 中更详细地介绍 vector，
// 但现在只需要知道 vector 本质上是动态数组，类型 std::vector<std::string> 是一个字符串数组。
// 主要的是，vector 会占用不可忽略的内存量，这里用它来展示使用 std::move 的性能优势。
#include <vector>

// 基本的 Person 类，实现了移动构造函数和移动赋值运算符，
// 并删除了拷贝构造函数和拷贝赋值运算符。这意味着一旦 Person 对象被实例化，它就不能被复制。
// 它必须从一个左值移动到另一个左值。
// 没有拷贝运算符的类在只需要一个类的定义实例时很有用。
// 例如，如果一个类管理一个动态分配的内存块，那么在没有适当处理的情况下
// 创建此类的多个实例可能导致双重删除或内存泄漏。
class Person {
public:
  Person() : age_(0), nicknames_({}), valid_(true) {}

  // 请记住，此构造函数接受一个 std::vector<std::string> 右值。
  // 这使构造函数更高效，因为它在构造 person 对象时不会深拷贝 vector 实例。
  Person(uint32_t age, std::vector<std::string> &&nicknames)
      : age_(age), nicknames_(std::move(nicknames)), valid_(true) {}

  // Person 类的移动构造函数。它接受一个 Person 类型的右值，
  // 并将作为参数传入的右值的内容移动到此 Person 对象实例中。
  // 注意 std::move 的使用。为了确保对象 person 中的 nicknames 被移动而不是深拷贝，
  // 我们使用 std::move。
  // std::move 会将左值 person.nicknames_ 转换为右值，表示值本身。
  // 还要注意，我没有对 age_ 字段调用 std::move。
  // 由于它是整数类型，太小了不会产生显著的拷贝成本。
  // 一般来说，对于数值类型，可以拷贝它们，但对于其他类型，
  // 如字符串和对象类型，除非需要拷贝，否则应该移动类实例。
  Person(Person &&person)
      : age_(person.age_), nicknames_(std::move(person.nicknames_)),
        valid_(true) {
    std::cout << "Calling the move constructor for class Person.\n";
    // 被移动对象的有效性标记被设置为 false。
    person.valid_ = false;
  }

  // Person 类的移动赋值运算符。
  Person &operator=(Person &&other) {
    std::cout << "Calling the move assignment operator for class Person.\n";
    age_ = other.age_;
    nicknames_ = std::move(other.nicknames_);
    valid_ = true;

    // 被移动对象的有效性标记被设置为 false。
    other.valid_ = false;
    return *this;
  }

  // 我们删除拷贝构造函数和拷贝赋值运算符，
  // 所以这个类不能被拷贝构造。
  Person(const Person &) = delete;
  Person &operator=(const Person &) = delete;

  uint32_t GetAge() { return age_; }

  // 返回类型中的这个 & 符号意味着我们返回对 nicknames_[i] 处字符串的引用。
  // 这也意味着我们不拷贝结果字符串，
  // 此函数返回的内存地址实际上是指向向量 nicknames_ 内存的地址。
  std::string &GetNicknameAtI(size_t i) { return nicknames_[i]; }

  void PrintValid() {
     if (valid_) {
      std::cout << "Object is valid." << std::endl;
    } else {
      std::cout << "Object is invalid." << std::endl;
    }
  }

private:
  uint32_t age_;
  std::vector<std::string> nicknames_;
  // 跟踪对象的数据是否有效，即是否所有数据都已移动到另一个实例。
  bool valid_;
};

int main() {
  // 让我们看看如何在类中实现和使用移动构造函数和移动赋值运算符。
  // 首先，我们创建一个 Person 类的实例。
  // 注意对象 andy 是一个有效的对象。
  Person andy(15445, {"andy", "pavlo"});
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // 要将 andy 对象的内容移动到另一个对象，我们可以用几种方式使用 std::move。
  // 这种方法调用移动赋值运算符。
  Person andy1;
  andy1 = std::move(andy);

  // 注意 andy1 是有效的，而 andy 不是有效对象。
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // 这种方法调用移动构造函数。在此操作之后，原始 andy 对象的内容
  // 已移动到 andy1，然后移动到 andy2。andy 和 andy1 左值实际上失效了
  //（不应再使用，除非重新初始化）。
  Person andy2(std::move(andy1));

  // 注意 andy2 是有效的，而 andy1 不是有效对象。
  std::cout << "Printing andy2's validity: ";
  andy2.PrintValid();
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();

  // 但是，请注意，由于拷贝赋值运算符被删除，此代码将无法编译。
  // 此代码的第一行通过默认构造函数构造一个新对象，
  // 第二行调用拷贝赋值运算符用 andy2 的深拷贝内容重新初始化 andy3。
  // 尝试取消注释这些代码行以查看生成的编译器错误。
  // Person andy3;
  // andy3 = andy2;

  // 由于拷贝构造函数被删除，此代码将无法编译。
  // 尝试取消注释此代码以查看生成的编译器错误。
  // Person andy4(andy2);

  return 0;
}