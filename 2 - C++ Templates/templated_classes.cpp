// 包含 std::cout（用于输出）。
#include <iostream>

// 模板也可以用于实现类。例如，这里是一个基本的模板类，
// 它存储一个模板类型的元素，并在调用print函数时打印它。
template<typename T>
class Foo {
  public:
    Foo(T var) : var_(var) {}
    void print() {
      std::cout << var_ << std::endl;
    }
  private:
    T var_;
};

// 你也可以通过模板向类传递多个类型名称。
// 例如，这里是另一个基本的模板类，它存储两个模板类型的元素，
// 并在调用print函数时打印它们。
template<typename T, typename U> 
class Foo2 {
  public:
    Foo2(T var1, U var2) 
      : var1_(var1)
      , var2_(var2) {}
    void print() {
      std::cout << var1_ << " and " << var2_ << std::endl;
    }
  private:
    T var1_;
    U var2_;
};

// 也可以创建特化的模板类，对不同类型执行不同的操作。
// 看下面这个刻意设计的例子，它实例化一个类，
// 其print函数在存储的变量是除了float之外的任何其他类型时，输出该变量的值。
// 如果该类是用float类型实例化的，它会打印出"hello float"
// 和该类在其var_字段中存储的变量。
template<typename T>
class FooSpecial {
  public:
    FooSpecial(T var) : var_(var) {}
    void print() {
      std::cout << var_ << std::endl;
    }
  private:
    T var_;
};

// 特化的模板类，专门化于float类型。
template<>
class FooSpecial<float> {
  public:
    FooSpecial(float var) : var_(var) {}
    void print() {
      std::cout << "hello float! " << var_ << std::endl;
    }
  private:
    float var_;
};

// 模板参数不一定要是类型。它们也可以是值！
template<int T>
class Bar {
  public: 
    Bar() {}
    void print_int() {
      std::cout << "print int: " << T << std::endl;
    }
};

int main() {
  // 首先，让我们从模板类构造一个对象。Foo类模板用int模板参数实例化。
  // 这会使a的类型变成Foo<int>而不是Foo。a的print函数按预期工作。
  Foo<int> a(3);
  std::cout << "Calling print on Foo<int> a(3): ";
  a.print();

  // 模板类也可以解释其参数的类型。再次提醒，如果你是初学者，
  // 在不确定要实例化类的类型时，请三思而后行。
  Foo b(3.4f);
  std::cout << "Calling print on Foo b(3.4f): ";
  b.print();

  // 其次，我们从具有多个类型参数的模板类构造一个对象。
  Foo2<int, float> c(3, 3.2f);
  std::cout << "Calling print on Foo2<int, float> c(3, 3.2f): ";
  c.print();

  // 让我们看看当我们用float类型参数和不用float类型参数实例化FooSpecial时会发生什么。
  // 正如预期的那样，当我们从d调用print时，
  // 它打印变量而不是"hello float"。当我们从e调用print时，
  // e是实例化的FooSpecial<float>类的实例，它打印"hello float！"
  FooSpecial<int> d(5);
  std::cout << "Calling print on FooSpecial<int> d(5): ";
  d.print();

  FooSpecial<float> e(4.5);
  std::cout << "Calling print on FooSpecial<float> e(4.5): ";
  e.print();

  // 最后，让我们看看当我们从具有非类型参数的模板类构造对象时会发生什么。
  Bar<150> f;
  std::cout << "Calling print_int on Bar<150> f: ";
  f.print_int();

  // 再次强调，这些都是刻意设计的例子，但理解它们仍然很重要，
  // 因为你会在Bustub代码库中看到类似的代码，所以在这些上下文中
  // 理解模板类是很有用的！

  return 0;
}