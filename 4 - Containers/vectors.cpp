// C++ STL 包含一个容器库，它是数据结构和算法实现的通用集合，
// 允许用户轻松操作堆栈、队列和哈希表等数据结构。
// 每个容器都有自己的头文件和用法。
// 在 C++ 标准中（直到 C++ 23），目前有 20 个容器，这里无法很好地全部涵盖。
// 在这个文件中，我们将介绍容器 std::vector。
// std::vector 容器本质上是一个通用动态数组（或无界数组）。
// 我们无法涵盖这个容器中的每一个函数，
// 但我们将尝试涵盖使用这个容器的基础知识。

// 在 https://en.cppreference.com/w/cpp/container 
// 上有关于所有其他函数和其他容器的文档。
// 在完成这门课的作业时你肯定需要这个资源，
// 所以你应该去看看！

// 包含 std::remove_if 以从向量中移除元素。
#include <algorithm>
// 包含 std::cout（用于打印）以进行演示。
#include <iostream>
// 包含向量容器库头文件。
#include <vector>

// 基本点类。（稍后会使用）
class Point {
public:
  Point() : x_(0), y_(0) {
    std::cout << "Default constructor for the Point class is called.\n";
  }

  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Custom constructor for the Point class is called.\n";
  }

  inline int GetX() const { return x_; }
  inline int GetY() const { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }
  void PrintPoint() const {
    std::cout << "Point value is (" << x_ << ", " << y_ << ")\n";
  }

private:
  int x_;
  int y_;
};

// 一个打印 int 向量元素的实用函数。
// 这里的代码应该是可以理解的，
// 并且与 main 函数中遍历向量元素的代码相似。
void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

int main() {
  // 我们可以用以下语法声明一个 Point 向量。
  std::vector<Point> point_vector;

  // 也可以通过初始化列表来初始化向量。
  std::vector<int> int_vector = {0, 1, 2, 3, 4, 5, 6};

  // 有两个函数可以向向量后端追加数据。
  // 它们是 push_back 和 emplace_back。
  // 通常，emplace_back 稍微快一些，
  // 因为它将构造函数参数转发给对象的构造函数并就地构造对象，
  // 而 push_back 先构造对象，然后将其移动到向量中的内存。
  // 我们可以在这里看到，我们向向量中添加两个 Point 对象。
  std::cout << "Appending to the point_vector via push_back:\n";
  point_vector.push_back(Point(35, 36));
  std::cout << "Appending to the point_vector via emplace_back:\n";
  point_vector.emplace_back(37, 38);

  // 让我们向 point_vector 的后端添加更多项目。
  point_vector.emplace_back(39, 40);
  point_vector.emplace_back(41, 42);

  // 有很多方法可以遍历向量。
  // 例如，我们可以通过以下 for 循环遍历它的索引。
  // 注意，对于数组或向量索引使用无符号整数类型是好习惯。
  std::cout << "Printing the items in point_vector:\n";
  for (size_t i = 0; i < point_vector.size(); ++i) {
    point_vector[i].PrintPoint();
  }

  // 我们也可以通过 for-each 循环遍历它。
  // 注意我使用引用来遍历它，
  // 这样我们遍历的项目就是原始向量中的项目。
  // 如果我们通过向量元素的引用进行迭代，
  // 我们也可以修改向量中的数据。
  for (Point &item : point_vector) {
    item.SetY(445);
  }

  // 让我们看看我们的更改是否生效。
  // 注意我使用 const 引用语法来确保我访问的数据是只读的。
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // 现在，我们展示如何从向量中删除元素。
  // 首先，我们可以通过 erase 函数按位置删除元素。
  // 例如，如果我们想删除 int_vector[2]，
  // 我们可以用以下参数调用以下函数。
  // 传递给此 erase 函数的参数具有类型std::vector<int>::iterator。
  // C++ STL 容器的迭代器是指向容器内元素的对象。
  // 例如，int_vector.begin() 是指向向量中第一个元素的迭代器对象。
  // 向量迭代器还有一个加号操作符，
  // 它接受一个向量迭代器和一个整数。
  // 加号操作符将迭代器指向的元素索引增加传入的数字。
  // 因此，int_vector.begin() + 2 指向向量中的第三个元素，
  // 或者 int_vector[2] 处的元素。
  // 如果你对迭代器感到困惑，阅读 iterator.cpp 的头部可能会有帮助。
  int_vector.erase(int_vector.begin() + 2);
  std::cout << "Printing the elements of int_vector after erasing "
               "int_vector[2] (which is 2)\n";
  print_int_vector(int_vector);

  // 我们也可以通过 erase 函数删除一个范围内的元素。
  // 如果我们想删除从索引 1 到数组末尾的元素，那么我们可以如下操作。
  // 注意 int_vector.end() 是指向向量末尾的迭代器。
  // 它不指向向量的最后一个有效索引。
  // 它指向向量的末尾，无法访问数据。
  int_vector.erase(int_vector.begin() + 1, int_vector.end());
  std::cout << "Printing the elements of int_vector after erasing all elements "
               "from index 1 through the end\n";
  print_int_vector(int_vector);

  // 我们也可以通过过滤来删除值，即如果值满足条件就删除它们。
  // 我们可以通过导入另一个库，即算法库来做到这一点，
  // 它给我们提供了std::remove_if 函数，
  // 该函数从迭代器范围中移除所有满足条件的元素。
  // 这确实看起来非常复杂，但代码可以总结如下。
  // std::remove_if 接受 3 个参数。
  // 其中两个参数指示我们应该过滤的元素范围。
  // 这些由 point_vector.begin() 和 point_vector.end() 给出，
  // 它们是分别指向向量开头和结尾的迭代器。
  // 因此，当我们传递这些时，我们暗示我们希望整个向量被过滤。
  // 第三个参数是一个条件 lambda 类型（参见 C++ 中的 std::function 库，
  // 或者在 https://en.cppreference.com/w/cpp/utility/functional/function），
  // 它接受一个参数，该参数应该代表我们正在过滤的向量中的每个元素。
  // 这个函数应该返回一个布尔值，如果元素要被过滤掉则为 true，否则为 false。
  // std::remove_if 返回一个指向容器中应该被消除的第一个元素的迭代器。
  // 请记住，它会根据需要交换元素，
  // 将需要删除的元素分区到它返回的迭代器值之后。
  // 当调用 erase 时，它只删除 remove_if 已分区要删除的元素，
  // 直到向量的末尾。
  // 这个外部 erase 接受一个范围参数，
  // 正如我们在前面的例子中看到的。
  point_vector.erase(
      std::remove_if(point_vector.begin(), point_vector.end(),
                     [](const Point &point) { return point.GetX() == 37; }),
      point_vector.end());

  // 在这里调用 remove 后，我们应该看到我们的点向量中剩下三个元素。
  // 只有值为 (37, 445) 的那个被删除了。
  std::cout << "Printing the point_vector after (37, 445) is erased:\n";
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // 我们在 auto.cpp 中讨论更有风格和可读性的遍历 C++ STL 容器的方法！
  // 如果你感兴趣的话可以看看。

  return 0;
}