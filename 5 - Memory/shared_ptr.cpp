// 在这个文件中，我们将讨论std::shared_ptr，它是一个C++智能指针。
// 请查看unique_ptr.cpp的介绍以了解智能指针的介绍。
// std::shared_ptr是一种智能指针类型，
// 它通过指针保持对对象的共享所有权。
// 这意味着多个shared pointer可以拥有同一个对象，
// 并且shared pointer可以被复制。

// 包含std::cout（打印）用于演示目的。
#include <iostream>
// 包含std::shared_ptr功能。
#include <memory>
// 包含用于std::move的utility头文件。
#include <utility>

// 基础Point类。（稍后将使用）
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

// 通过将shared pointer参数作为引用传递来修改shared pointer内Point对象的函数。
void modify_ptr_via_ref(std::shared_ptr<Point> &point) { point->SetX(15); }

// 通过将shared pointer参数作为右值引用传递来修改shared pointer内Point对象的函数。
void modify_ptr_via_rvalue_ref(std::shared_ptr<Point> &&point) {
  point->SetY(645);
}

void copy_shared_ptr_in_function(std::shared_ptr<Point> point) {
  std::cout << "Use count of shared pointer is " << point.use_count()
            << std::endl;
}

int main() {
  // 这是如何初始化一个std::shared_ptr<Point>类型的空shared pointer。
  std::shared_ptr<Point> s1;
  // 这是如何使用默认构造函数初始化shared pointer。
  std::shared_ptr<Point> s2 = std::make_shared<Point>();
  // 这是如何使用自定义构造函数初始化shared pointer。
  std::shared_ptr<Point> s3 = std::make_shared<Point>(2, 3);

  // 检查智能指针是否为空的具体语法在unique_ptr.cpp中介绍。
  // 注意s1是空的，而s2和s3不是空的。
  std::cout << "Pointer s1 is " << (s1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer s2 is " << (s2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer s3 is " << (s3 ? "not empty" : "empty") << std::endl;

  // 可以通过复制赋值和复制构造函数运算符来复制shared pointer。
  // 使用这些复制运算符将增加整个对象的引用计数。
  // 另外，std::shared_ptr带有一个名为use_count的方法，
  // 它跟踪当前与当前shared pointer实例相同内部数据交互的对象数量。

  // 首先，获取指针s3的引用数量。
  // 这应该是1，因为s3是使用s3中数据的唯一对象实例。
  std::cout
      << "Number of shared pointer object instances using the data in s3: "
      << s3.use_count() << std::endl;

  // 然后，s4从s3复制构造。
  // 这是复制构造，因为这是s4第一次出现。
  std::shared_ptr<Point> s4 = s3;

  // 现在，指针s3数据的引用数量应该是2，
  // 因为s4和s3都可以访问s3的数据。
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after one copy: "
            << s3.use_count() << std::endl;

  // 然后，s5从s4复制构造。
  std::shared_ptr<Point> s5(s4);

  // 现在，指针s3数据的引用数量应该是3，
  // 因为s5、s4和s3都可以访问s3的数据。
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after two copies: "
            << s3.use_count() << std::endl;

  // 修改s3的数据也应该改变s4和s5中的数据，
  // 因为它们引用相同的对象实例。
  s3->SetX(445);

  std::cout << "Printing x in s3: " << s3->GetX() << std::endl;
  std::cout << "Printing x in s4: " << s4->GetX() << std::endl;
  std::cout << "Printing x in s5: " << s5->GetX() << std::endl;

  // 也可以通过移动来转移std::shared_ptr的所有权。
  // 注意指针在移动发生后为空。
  std::shared_ptr<Point> s6 = std::move(s5);

  // 注意s5现在是空的，s6引用与s3和s4相同的数据，
  // 并且仍然有3个shared pointer实例可以访问相同的Point实例数据，
  // 而不是4个。
  std::cout << "Pointer s5 is " << (s5 ? "not empty" : "empty") << std::endl;
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after two copies and a move: "
            << s3.use_count() << std::endl;

  // 与unique pointer类似，
  // shared pointer也可以通过引用和右值引用传递。
  // 请参见unique_ptr.cpp了解通过引用传递unique pointer的信息。
  // 请参见references.cpp了解更多关于引用的信息。
  // 请参见move_semantics.cpp了解更多关于右值引用的信息。
  // 这里，我们展示下面的代码，
  // 调用通过将shared pointer作为引用和右值引用传递来修改s2的函数。
  modify_ptr_via_ref(s2);
  modify_ptr_via_rvalue_ref(std::move(s2));

  // 运行此代码后，s2应该有x = 15和y = 645。
  std::cout << "Pointer s2 has x=" << s2->GetX() << " and y=" << s2->GetY()
            << std::endl;

  // 与unique pointer不同，shared pointer也可以按值传递。
  // 在这种情况下，函数包含自己的shared pointer副本，
  // 该副本在函数结束后会自我销毁。
  // 在这个例子中，在s2按值传递给函数之前，它的use count是1。
  // 当它在函数中时，它的use count是2，
  // 因为函数中的shared pointer实例中有s2数据的另一个副本。
  // 函数超出作用域后，函数中的这个对象被销毁，
  // use count返回到1。
  std::cout
      << "Number of shared pointer object instances using the data in s2: "
      << s2.use_count() << std::endl;
  copy_shared_ptr_in_function(s2);
  std::cout << "Number of shared pointer object instances using the data in s2 "
               "after calling copy_shared_ptr_in_function: "
            << s2.use_count() << std::endl;

  return 0;
}