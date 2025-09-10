#include <iostream>
#include <memory>
#include <utility>

// 这个文件包含在Spring2024 15-445/645 C++训练营中使用的代码。
// 它通过从头实现一个简单版本的unique_ptr，深入探讨了C++的新特性，
// 如移动构造函数/赋值运算符、移动语义、unique_ptr、shared_ptr、包装类等。

// **重要说明**:
//   1. 在阅读此文件之前，请先阅读`src`中的`move_semantics.cpp`和`move_constructors.cpp`！
//   2. 请从MAIN函数开始阅读！

// 这是我们对std::unique_pointer<T>的实现，真正的实现更复杂！
// 模板允许我们在代码中稍后用我们想要的任何类型T来替换。
template <typename T>
class Pointer {
 public:
  Pointer() {
    ptr_ = new T;
    *ptr_ = 0;
    std::cout << "New object on the heap: " << *ptr_ << std::endl;
  }
  Pointer(T val) {
    ptr_ = new T;
    *ptr_ = val;
    std::cout << "New object on the heap: " << val << std::endl;
  }
  // 析构函数在实例超出作用域时被调用（就在栈弹出时）。
  ~Pointer() {
    if (ptr_) {
      std::cout << "Freed: " << *ptr_ << std::endl;
      delete ptr_;
    }
  }

  // 复制构造函数被显式删除。
  Pointer(const Pointer<T> &) = delete;
  // 复制赋值运算符被显式删除。
  Pointer<T> &operator=(const Pointer<T> &) = delete;

  // 添加移动构造函数：当我们需要延长对象的生命周期时很有用！
  Pointer<T>(Pointer<T> &&another) : ptr_(another.ptr_) { another.ptr_ = nullptr; }
  // 添加移动赋值运算符：当我们需要延长对象的生命周期时很有用！
  Pointer<T> &operator=(Pointer<T> &&another) {
    if (ptr_ == another.ptr_) {  // In case `p = std::move(p);`
      return *this;
    }
    if (ptr_) {  // We must free the existing pointer before overwriting it! Otherwise we LEAK!!
      delete ptr_;
    }
    ptr_ = another.ptr_;
    another.ptr_ = nullptr;  // NOTE: L14 avoids freeing nullptr during the destruction.
    return *this;
  }

  // 重载运算符*，以便让Pointer<T>感觉像一个"指针"。
  // 注意下面这行是我们可以在unique ptr类型上使用的以下语法的示例。
  // `p1.set_val(10)` -> `*p1 = 10`
  T &operator*() { return *ptr_; }

  T get_val() { return *ptr_; }
  void set_val(T val) { *ptr_ = val; }

 private:
  T *ptr_;
};

// smart_generator的错误版本
template <typename T>
Pointer<int> &dumb_generator(T init) {
  Pointer<T> p(init);
  return p;  // NOOO! A DANGLING REFERENCE!
}

template <typename T>
Pointer<T> smart_generator(T init) {
  Pointer<T> p(init);
  return std::move(p);
  // 实际上`return p`也可以工作，因为C++很智能，它知道在这个地方应该调用移动构造函数。
  // 你可以参考https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
  // 中的`Automatic l-values returned by value may be moved instead of copied`了解更多信息。
}

void take_ownership(std::unique_ptr<int> p) {
  // Do something...
}

void not_take_ownership(int *p) {
  // Never `delete p` here!!
}

int main() {
  /* ======================================================================
     === 第1部分：你在bustub中遇到的常见错误 ===============================
     ====================================================================== */
  // 在C++/这门课中编程时，你会看到一个叫做"unique_ptr"的变量类型...
  std::unique_ptr<int> ptr = std::make_unique<int>(3);
  // 这是什么意思？为什么我们不使用像`int *p = new int`这样的原始指针？（答案在第2部分）
  // 稍后，当你需要将这个unique_ptr传递给一个函数时，你可能会写以下代码
  //（请尝试取消注释下一行）...
  // take_ownership(ptr);
  // 它不工作。
  // 错误是`Call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'`。
  // 你可能会搜索互联网，其他人告诉你添加一个叫做`std::move`的东西...
  take_ownership(std::move(ptr));
  // 它工作了！看起来很好！然后你继续编程...
  // 稍后，你可能想再次使用p1（请尝试取消注释下一行）...
  // *ptr = 3;
  // 另一个错误:(，它说`segmentation fault`。
  // 看起来很混乱。到底发生了什么？
  // 我们将在这个训练营中解释它，通过从头实现一个简单版本的unique_ptr！

  /* ======================================================================
     === 第2部分：为什么我们需要unique_ptr而不是原始指针 ===================
     ====================================================================== */
  // 仅仅使用原始指针有什么问题？
  int *p = new int;  // Malloc
  *p = 456 * 12 / 34 + 23;
  if (*p == 76) {
    delete p;  // You may forget to add this line, and have `memory leak` problem!
    return 0;
  }
  delete p;  // Free

  // 原始指针很危险！如果你不注意，你会遇到内存泄漏、双重释放、释放后使用等问题...
  // 原因是在C++中，原始指针没有自动清理的内在机制！
  // 程序员必须自己分配和释放堆内存，这很容易出错。

  // 我们注意到，与堆中的内存不同，栈中的局部变量会自动创建和删除。
  // 我们能否将原始指针与栈中的局部变量绑定？
  // 这意味着，当这个局部变量被创建时，这个原始指针的堆内存会自动malloc。
  // 当这个局部变量死亡时，原始指针会自动释放。（更多详细信息：搜索RAII）

  // 让我们使用C++类来实现它！
  // 考虑一个类，它的唯一工作是持有和"拥有"一个原始指针，
  // 然后在类对象超出作用域时释放该指针...
  // 这个类被称为`智能指针`，unique_ptr是智能指针之一。
  // 但是，为什么我们不能复制unique_ptr？什么是std::move？

  /* ======================================================================
     === 第3部分：让我们从头实现一个unique_ptr类 ===========================
     ====================================================================== */
  // 我们只展示我们自己的unique_ptr类的最终版本。
  // 这是实现过程中的简要路线图：
  //  1. 第一版本：有默认复制构造函数和赋值运算符，没有移动构造函数和赋值运算符
  //     问题：`Pointer p2 = p1`会导致`double free`问题
  //     复制构造函数和赋值运算符在这种情况下是邪恶的，因为它会允许p1和p2都管理相同的
  //     原始指针！解决方案：禁用复制构造函数和赋值运算符
  //  2. 第二版本：没有复制构造函数和赋值运算符，没有移动构造函数和赋值运算符
  //     `Pointer p2 = p1`不会编译，这是好的。我们可以使用引用`Pointer &p2 = p1`代替。但是...
  //     问题：我们无法实现像dumb_generator()或smart_generator()这样的函数！
  //     解决方案：添加叫做移动构造函数和赋值运算符的东西
  //  3. 最终版本：没有复制构造函数和赋值运算符，有移动构造函数和赋值运算符
  //     `Pointer p4 = std::move(p3);`
  //     `std::move`保证这行代码调用`移动构造函数`（而不是`复制构造函数`），
  //     将原始指针的所有权从p3转移到p4！
  //     在这行之后，p3将不再有效！
  //     p3中的ptr_将为nullptr，除非你重新赋值，否则请不要再使用p3。
  // 现在你理解了什么是`std::move`，为什么复制函数被删除...以及如何使用unique_ptr！
  // 参考：Learncpp网站第22章
  // (https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/)
  Pointer<int> p1(4);
  std::cout << "Hi from p1 " << p1.get_val() << std::endl;
  p1.set_val(10);
  std::cout << "Hi again from p1 " << p1.get_val() << std::endl;

  {
    // 下一行的问题：两者都拥有这个原始指针的所有权！这里会双重释放！
    // Pointer<int> p2 = p1; // Code for 1st version implementation.
    // 解决方案：永远不允许复制指针的所有权！永远不要复制！
    // 删除复制赋值运算符和构造函数后，也许我们可以使用指针来重写`p2 = p1`。
    Pointer<int> *p2 = &p1;  // Code for 2nd version implementation.
    std::cout << "Hi from p2 " << p2->get_val() << std::endl;
    // 等等，这很愚蠢，我们又有了一个原始指针...也许我们可以使用C++引用，它更安全！
    // 它在语义上与`Pointer<int> *p2 = &p1`相同，除了程序员不**知道**指针
    // （即p2的地址）。
    Pointer<int> &p22 = p1;  // Code for 2nd version implementation.
    std::cout << "Hi from p22 " << p22.get_val() << std::endl;
  }
  // 但是引用并不能解决一切:(
  // 有时我们想使用堆来扩展栈的作用域，就像dumb_generator()所做的那样！
  // 例如：将一个元素从一个线程传递到另一个线程。
  // 请尝试取消注释以下代码！
  // Pointer<int>& dumb_pointer = dumb_generator(2); // Something will go horribly wrong, but what?
  // dumb_pointer.set_val(10); // Uh oh...

  // 我们需要一种"移动所有权"的方法。请检查Pointer类中的移动赋值运算符/构造函数。
  // 我们将dumb_generator()改为smart_generator()...
  // 最终版本实现的代码：
  Pointer<int> p3 = smart_generator<int>(2);
  p3.set_val(10);
  Pointer<int> p4 = std::move(p3);

  // 让我们让用户体验更好。
  // 1. 模板。
  Pointer<float> p5(5.1);
  std::cout << "Hi from float p5 " << p5.get_val() << std::endl;
  // 2. 运算符重载。
  Pointer<char> c1('a');
  *c1 = 'b';
  std::cout << "Hi from char c1 " << *c1 << std::endl;

  // 你可能对以下内容感到困惑：
  //  `Pointer<T> &&`（在移动构造函数和赋值运算符中）
  //                         VS
  //  `Pointer<T> &`（在复制构造函数和赋值运算符中）

  // 你现在有2个选择。首先，将其视为区分复制和移动的语法，直接跳到第4部分；
  // 其次，这里是一个快速解释：
  // 1. 你需要知道左值和右值。根据Abi的说法，左值的简化定义是左值是
  // 引用内存中位置的对象。右值是任何不是左值的东西。
  // 2. `Pointer<T> &&`是右值引用，而`Pointer<T> &`是左值引用。
  // 3. `std::move(p)`会将p从左值转换为某种东西，例如右值。
  // 4. 对于`Pointer p2 = p1`，它会调用复制构造函数，因为p1是左值。
  // 5. 对于`Pointer p2 = std::move(p1)`，它会调用移动构造函数，因为std::move(p1)是右值。

  /* ======================================================================
     === 第4部分：unique_ptr和shared_ptr的一些重要要点 ====================
     ====================================================================== */
  // unique_ptr的几个重要要点：（参考：https://www.learncpp.com/cpp-tutorial/stdunique_ptr/）
  // 1. 总是使用std::make_unique()来创建unique_ptr。
  std::unique_ptr<int> up{std::make_unique<int>(1)};
  // 请避免编写以下代码！
  // int *rp = new int;
  // std::unique_ptr<int> up1{ rp };
  // std::unique_ptr<int> up2{ rp }; // WRONG!

  // 2. 将std::unique_ptr传递给函数的方法。
  not_take_ownership(up.get());
  // Unique_ptr `up`在这里仍然有效！
  take_ownership(std::move(up));
  // Unique_ptr `up`在这里不能使用！

  // shared_ptr的几个重要要点：（参考：https://www.learncpp.com/cpp-tutorial/stdshared_ptr/）
  // 0. 多个shared ptr可以同时拥有原始指针的所有权。
  //    Shared_ptr会计算拥有相同原始指针的shared ptr的数量，
  //    **只有当**count == 0时才释放原始指针。
  std::shared_ptr<int> sp1{std::make_shared<int>(1)};
  {
    // 你可以对shared_ptr使用复制构造函数和赋值运算符。
    std::shared_ptr<int> sp2 = sp1;
    std::cout << "Count: " << sp1.use_count() << std::endl;  // Output: 2
  }
  std::cout << "Count: " << sp1.use_count() << std::endl;  // Output: 1
  // 1. 总是复制现有的std::shared_ptr。
  int *rp = new int;
  std::shared_ptr<int> sp3{rp};
  // std::shared_ptr<int> sp4{ rp }; // WRONG!
  std::shared_ptr<int> sp4{sp3};
  // 2. 总是使用std::make_shared()来创建shared_ptr。

  return 0;
}