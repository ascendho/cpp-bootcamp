// 包含 std::cout (用于打印) 以进行演示。
#include <iostream>

// 模板是 C++ 中的一项语言特性，允许您编写可以处理多种数据类型的代码，而无需实际指定这些类型。
// 在 C++ 中，您可以创建模板函数和模板类。我们将在此文件中讨论模板函数。

// 这是一个对两个数字求和的基本模板函数。
// 语法注意：您会看到同时使用 template<class T> 和 template<typename T> 的代码。
// 虽然这些语句是等价的，但 class 和 typename 关键字之间有差异。
// 这篇博客文章涵盖了这种差异，但您在这门课中不需要了解这个：
// https://mariusbancila.ro/blog/2021/03/15/typename-or-class/
template <typename T> T add(T a, T b) { return a + b; }

// 可以通过模板向函数传递多个类型名。
// 此函数将打印出这两个值。
template<typename T, typename U>
void print_two_values(T a, U b) {
  std::cout << a << " and " << b << std::endl;
}

// 也可以创建特化的模板函数，为不同类型做不同的事情。
// 以下面这个人为的例子为例，如果是 float 类型则打印类型，
// 但对于所有其他类型则只打印 hello world。
template <typename T> void print_msg() { std::cout << "Hello world!\n"; }

// 针对 float 类型特化的模板函数。
template <> void print_msg<float>() {
  std::cout << "print_msg called with float type!\n";
}

// 最后，模板参数不必是类。以这个基本（但非常人为的）函数为例，
// 它接受一个 bool 作为模板参数，并根据布尔参数对参数做不同的处理。
template <bool T> int add3(int a) {
  if (T) {
    return a + 3;
  }

  return a;
}

int main() {
  // 首先，让我们看看 add 函数在 int 和 float 上的调用。
  std::cout << "Printing add<int>(3, 5): " << add<int>(3, 5) << std::endl;
  std::cout << "Printing add<float>(2.8, 3.7): " << add<float>(2.8, 3.7)
            << std::endl;

  // 模板函数也可以解释其参数的类型，虽然如果您是现代 C++ 的初学者，
  // 但建议您不要这样做，因为这样您可能不确定传递给函数的类型。
  std::cout << "Printing add(3, 5): " << add(3, 5) << std::endl;

  // 其次，让我们看看用两种不同类型调用 print_two_values 函数。
  std::cout << "Printing print_two_values<int, float>(3, 3.2): ";
  print_two_values<int, float>(3, 3.2);

  // 让我们看看当我们调用 print_msg 时传入和不传入 float 类型会发生什么。
  // 如预期的那样，第一次调用 print_msg 打印出通用输出，
  // 而第二次调用使用 float 参数，识别其类型参数并调用特化函数。
  std::cout << "Calling print_msg<int>(): ";
  print_msg<int>();
  std::cout << "Calling print_msg<float>(): ";
  print_msg<float>();

  // add3 对于 true 和 false 模板参数都有指定的行为，
  // 正如我们在这里看到的。
  std::cout << "Printing add3<true>(3): " << add3<true>(3) << std::endl;
  std::cout << "Printing add3<false>(3): " << add3<false>(3) << std::endl;

  // 最后，重要的是要注意这些大多数都是人为的例子，
  // 可以在不使用模板的情况下编写其中一些函数（例如，传递布尔值作为参数而不是模板参数）。
  // 但是，在这门课中，您将在代码库中看到类似的代码，
  // 所以在这些上下文中理解模板函数是很好的！

  return 0;
}