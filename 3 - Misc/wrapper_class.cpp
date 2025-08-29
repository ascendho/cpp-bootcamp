// C++ 包装类是管理资源的类。资源可以是内存、文件套接字或网络连接。
// 包装类通常使用 RAII（资源获取即初始化）C++ 编程技术。
// 使用这种技术意味着资源的生命周期与其作用域绑定。
// 当包装类的实例被构造时，这意味着它所管理的底层资源是可用的，
// 当这个实例被析构时，资源也变得不可用。
// 以下是一些关于 RAII 的有用资源：
// https://en.cppreference.com/w/cpp/language/raii (CPP 文档网站上的 RAII 文档)
// Stack Overflow 上关于"什么是 RAII？"的有趣回答：
// https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii

// 在这个文件中，我们将查看管理 int* 的包装类的基本实现。
// 我们还将查看这个类的使用方法。

// 包含 std::cout（用于打印）以进行演示。
#include <iostream>
// 包含 utility 头文件以使用 std::move。
#include <utility>

// IntPtrManager 类是管理 int* 的包装类。这个类管理的资源是通过指针 ptr_ 可访问的动态内存。
// 根据 RAII 技术的原则，包装类对象不应该是可复制的，因为一个对象应该管理一个资源。
// 因此，拷贝赋值操作符和拷贝构造函数从这个类中被删除。
// 但是，这个类仍然可以从不同的左值/所有者之间移动，并且有移动构造函数和移动赋值操作符。
// 包装类禁止复制的另一个原因是它们在析构函数中销毁资源，
// 如果两个对象管理同一个资源，就有重复删除资源的风险。
class IntPtrManager {
  public:
    // 包装类的所有构造函数都应该初始化一个资源。
    // 在这种情况下，这意味着分配我们正在管理的内存。
    // 这个指针数据的默认值是 0。
    IntPtrManager() {
      ptr_ = new int;
      *ptr_ = 0;
    }

    // 这个包装类的另一个构造函数，接受一个初始值。
    IntPtrManager(int val) {
      ptr_ = new int;
      *ptr_ = val;
    }

    // 包装类的析构函数。析构函数必须销毁它正在管理的资源；
    // 在这种情况下，析构函数删除指针！
    ~IntPtrManager() {
      // 注意，由于移动构造函数通过将 ptr_ 值设置为 nullptr 来标记对象无效，
      // 我们必须在析构函数中考虑这一点。
      // 我们不想对 nullptr 调用 delete！
      if (ptr_) {
        delete ptr_;
      }
    }

    // 这个包装类的移动构造函数。注意在移动构造函数被调用后，
    // 实际上将 other 的所有数据移动到被构造的指定实例中，
    // other 对象不再是 IntPtrManager 类的有效实例，
    // 因为它没有内存可以管理。
    IntPtrManager(IntPtrManager&& other) {
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }

    // 这个包装类的移动赋值操作符。
    // 与移动构造函数类似的技术。
    IntPtrManager &operator=(IntPtrManager &&other) {
      if (ptr_ == other.ptr_) {
        return *this;
      }
      if (ptr_) {
        delete ptr_;
      }
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
      return *this;
    }

    // 我们删除拷贝构造函数和拷贝赋值操作符，
    // 所以这个类不能被拷贝构造。
    IntPtrManager(const IntPtrManager &) = delete;
    IntPtrManager &operator=(const IntPtrManager &) = delete;

    // 设置函数。
    void SetVal(int val) {
      *ptr_ = val;
    }

    // 获取函数。
    int GetVal() const {
      return *ptr_;
    }

  private:
    int *ptr_;

};

int main() {
  // 我们初始化一个 IntPtrManager 的实例。
  // 在它被初始化后，
  // 这个类正在管理一个 int 指针。
  IntPtrManager a(445);

  // 获取值按预期工作。
  std::cout << "1. Value of a is " << a.GetVal() << std::endl;

  // 设置值成功，并且可以按预期检索值。
  a.SetVal(645);
  std::cout << "2. Value of a is " << a.GetVal() << std::endl;

  // 现在，我们通过移动构造函数将这个类的实例从 a 左值移动到 b 左值。
  IntPtrManager b(std::move(a));

  // 检索 b 的值按预期工作，
  // 因为 b 现在正在管理最初由创建 a 的构造函数构造的数据。
  // 注意在 a 上调用 GetVal() 会导致段错误，
  // a 在这种状态下应该实际上是空的和不可用的。
  std::cout << "Value of b is " << b.GetVal() << std::endl;

  // 一旦这个函数结束，a 和 b 的析构函数都会被调用。
  // a 的析构函数会注意到它正在管理的 ptr_ 已被设置为 nullptr，
  // 并且不会做任何事情，
  // 而 b 的析构函数应该释放它正在管理的内存。

  return 0;
}