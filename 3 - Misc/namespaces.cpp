// 命名空间为标识符（函数、类型、变量的名称）提供作用域。
// 它们用于将代码组织成逻辑组（例如，一个库可能是一个命名空间）。
// 它们还可以防止不同标识符之间的命名冲突。
// 例如，C++标准库使用std命名空间。
// 这就是为什么C++中的打印函数被标识为std::cout，
// 因为cout函数在std命名空间中声明。
// C++使用::运算符进行作用域解析，
// 因此它在区分函数、类型或类在哪个命名空间中声明方面很有用。

// 在这个文件中，我们将介绍命名空间、命名空间语法、using关键字，
// 以及从其他命名空间调用函数。

// 包含std::cout（打印）用于演示目的。
#include <iostream>

// 这是声明命名空间的语法。
namespace ABC {
  // 我们在ABC命名空间中定义一个函数spam。
  void spam(int a) {
    std::cout << "Hello from ABC::spam: " << a << std::endl;
  }

  // 命名空间DEF是一个嵌套命名空间，因为它在命名空间ABC内部声明。
  // 声明嵌套命名空间的语法与声明非嵌套命名空间的语法相同。
  namespace DEF {
    // 我们在N::M命名空间内定义一个函数bar。
    void bar(float a) {
      std::cout << "Hello from ABC::DEF::bar: " << a << std::endl;
    }

    // 我们在ABC::DEF命名空间内定义一个函数uses_bar。
    // 但是，由于bar与uses_bar在同一个命名空间中
    //（它们都在ABC::DEF命名空间中），
    // 函数bar在uses_bar函数中只需要通过名称引用。
    void uses_bar(float a) {
      std::cout << "Hello from uses_bar: ";
      bar(a);
    }

    // 我们在ABC::DEF命名空间中定义一个函数uses_spam。
    // 要从ABC::DEF命名空间引用ABC::spam，我们别无选择，
    // 只能通过其完整标识符引用它。
    // 尝试通过spam引用它将导致编译错误，(见下注释)
    // 声明不存在名为spam或ABC::DEF::spam的函数。
    // 注意，可以通过完整标识符引用每个函数，
    // 但这样做会使编码速度变得低效。
    void uses_spam(int a) {
      std::cout << "Hello from uses_spam: ";
      ABC::spam(a);

      // 尝试取消注释这段代码，它在这里调用spam(a)。
      // (注：原注释说这里会编译错误，
      // 然而本人根据实践得知，是可以编译通过的）
      // 参考资料：https://en.cppreference.com/w/cpp/language/unqualified_lookup.html
      // 已有人在原仓库中提出issue，见：https://github.com/cmu-db/15445-bootcamp/issues/22
      std::cout << "看起来是可以编译的！" << std::endl;
      spam(a);
    }
  }

  // 我们在ABC命名空间内但不在DEF命名空间内定义一个函数uses_DEF_bar。
  // 由于bar和uses_DEF_bar都在ABC命名空间中，
  // 函数bar在uses_DEF_bar函数中通过DEF::bar（区分命名空间）引用。
  void uses_DEF_bar(float a) {
    std::cout << "Hello from uses_DEF_bar: ";
    DEF::bar(a);
  }
}

// 命名空间A和命名空间B都有一个名为foo的函数，具有相同的参数和返回值。
// 这段代码能够编译是因为总体上，这两个foo函数有不同的完整标识符，
// 分别是A::foo和B::foo。
namespace A {
  void foo(int a) {
    std::cout << "Hello from A::foo: " << a << std::endl;
  }
}

namespace B {
  void foo(int a) {
    std::cout << "Hello from B::foo: " << a << std::endl;
  }

  void peloton(int a) {
    std::cout << "Hello from B::peloton: " << a << std::endl;
  }
}

namespace C {
  void eggs(int a) {
    std::cout << "Hello from C::eggs: " << a << std::endl;
  }
}


// using关键字的用途之一是将当前命名空间引入当前作用域。
// 这个语句将把命名空间B引入当前作用域。
// 这意味着B::foo可以在这行代码下面的任何地方通过foo引用。
// 在main中，我们将看到B::foo可以通过B::foo和foo引用。
using namespace B;

// using关键字的另一个用途是将命名空间的某些成员引入当前作用域。
// 这个语句将把C::eggs引入当前作用域。
// 这意味着eggs可以在这行代码下面的任何地方通过eggs引用。
using C::eggs;

int main() {
  // 下面这行代码调用函数spam。
  // 调用spam(2)将不起作用，
  // 因为没有标识符为spam的函数，只有ABC::spam。
  ABC::spam(2);

  // 下面这行代码调用函数bar。
  ABC::DEF::bar(4.45);

  // 下面这行代码调用uses_bar。
  // 如预期的那样，uses_bar将打印"Hello from uses_bar"，
  // 然后调用ABC::DEF::bar。
  ABC::DEF::uses_bar(6.45);

  // 下面这行代码调用uses_spam。
  // 如预期的那样，uses_spam将打印"Hello from uses_spam"，
  // 然后调用ABC::spam。
  ABC::DEF::uses_spam(37);

  // 下面这行代码调用uses_DEF_bar。
  // 如预期的那样，uses_DEF_bar将打印"Hello from uses_DEF_bar"，
  // 然后调用ABC::DEF::bar。
  ABC::uses_DEF_bar(3.12);

  // 现在，让我们谈论两个foo函数。
  // A::foo和B::foo是具有相同参数的不同函数，
  // 但它们被允许共存，因为它们有不同的标识符。
  A::foo(122);
  B::foo(150);

  // 但是，由于将B命名空间引入当前作用域，
  // 可以在不使用B命名空间标识符的情况下访问B命名空间中的任何内容。
  // 因此，可以通过将B::foo标识为foo来调用它。
  foo(440);

  // 同样，由于整个命名空间B被引入当前作用域，
  // 也可以将B::peloton（命名空间B中的另一个函数）引用为peloton。
  peloton(721);

  // 记住，使用using关键字将整个命名空间引入当前作用域可能是有风险的，
  // 如果你不小心，可能会遇到命名冲突。
  // 因此，我们不建议你这样做。
  // 但是，可以将命名空间的某些成员引入当前作用域，
  // 这里，我们通过将C::eggs标识为eggs来引用它。
  eggs(999);

  return 0;
}