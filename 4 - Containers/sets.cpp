// 在这个文件中，我们将介绍容器std::set。
// 我们无法涵盖这个容器中的每个函数，
// 但我们将尝试涵盖使用这个容器的基础知识。
// 查看vectors.cpp的介绍以获得C++ STL容器的一般概述。

// std::set容器是一个数据结构，包含单一类型的唯一对象的有序集合。
// 它通常实现为红黑树，如果这有助于你理解std::set的话。
// std::set容器用于维护一组唯一元素。

// 关于所有其他函数和其他容器的文档
// 可以在 https://en.cppreference.com/w/cpp/container 找到。
// 在完成这门课的作业时你肯定需要这个资源，所以你应该查看一下！

// 包含std::cout（打印）用于演示目的。
#include <iostream>
// 包含set容器库头文件。
#include <set>

int main() {
  // 我们可以用以下语法声明一个int类型的set。
  std::set<int> int_set;

  // 要插入元素，我们使用insert函数。
  // 这里我们在set中插入元素1到10。
  // 还有一个emplace函数，允许用户就地构造对象进行set插入。
  // 我们在 vectors.cpp（第73行）中更详细地介绍emplace。
  for (int i = 1; i <= 5; ++i) {
    int_set.insert(i);
  }

  for (int i = 6; i <= 10; ++i) {
    int_set.emplace(i);
  }

  // 要查找元素，我们可以使用find函数，
  // 它返回一个迭代器，指向set中与键参数等价的键的元素。
  // 然后我们可以检查这个返回的迭代器是否等价于end迭代器。
  // 如果返回的迭代器值等价于end迭代器值，
  // 那么这意味着元素不存在。
  std::set<int>::iterator search = int_set.find(2);
  if (search != int_set.end()) {
    std::cout << "Element 2 is in int_set.\n";
  }

  // 我们也可以使用count函数，它返回set中具有指定键的元素数量。
  if (int_set.count(11) == 0) {
    std::cout << "Element 11 is not in the set.\n";
  }

  if (int_set.count(3) == 1) {
    std::cout << "Element 3 is in the set.\n";
  }

  // 要删除元素，我们可以使用erase函数。
  // erase函数首先可以接受一个要删除的键。
  // 例如，如果我们想从set中删除4，我们可以调用：
  int_set.erase(4);

  // 我们确认4不再在set中了。
  if (int_set.count(4) == 0) {
    std::cout << "Element 4 is not in the set.\n";
  }

  // 另外，如果我们想删除某个位置的元素，
  // 我们可以向erase函数传递一个迭代器。
  // 假设我们想从set中删除第一个元素。
  // 我们可以向erase函数传递一个指向set中第一个元素的迭代器。
  int_set.erase(int_set.begin());

  // 我们确认1不再在set中了。
  if (int_set.count(1) == 0) {
    std::cout << "Element 1 is not in the set.\n";
  }

  // 最后，我们可以通过向erase函数传递迭代器范围来删除set中的元素。
  // 例如，如果我们想删除大于或等于9的元素（即9和10），我们调用以下代码。
  int_set.erase(int_set.find(9), int_set.end());

  // 我们确认9和10不再在set中了。
  if (int_set.count(9) == 0 && int_set.count(10) == 0) {
    std::cout << "Elements 9 and 10 are not in the set.\n";
  }

  // 我们可以通过set迭代器遍历set元素。
  // 你不能通过任何种类的索引遍历set。
  std::cout << "Printing the elements of the iterator:\n";
  for (std::set<int>::iterator it = int_set.begin(); it != int_set.end();
       ++it) {
    // 我们可以通过解引用迭代器来访问元素本身。
    std::cout << *it << " ";
  }
  std::cout << "\n";

  // 就像std::vector一样，我们也可以通过for-each循环遍历set。
  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const int &elem : int_set) {
    std::cout << elem << " ";
  }
  std::cout << "\n";

  // 我们在auto.cpp中讨论了遍历C++ STL容器的更具风格和可读性的方法！
  // 如果你感兴趣的话可以查看一下。

  return 0;
}