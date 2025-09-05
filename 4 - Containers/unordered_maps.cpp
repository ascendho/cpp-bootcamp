// 在这个文件中，我们将介绍容器std::unordered_map。
// 我们无法涵盖这个容器中的每个函数，
// 但我们将尝试涵盖使用这个容器的基础知识。
// 查看vectors.cpp的介绍以获得C++ STL容器的一般概述。

// 关于所有其他函数和其他容器的文档可以在
// https://en.cppreference.com/w/cpp/container 找到。
// 在完成这门课的作业时你肯定需要这个资源，
// 所以你应该查看一下！

// 包含std::cout（打印）用于演示目的。
#include <iostream>
// 包含unordered_map容器库头文件。
#include <unordered_map>
// 包含C++字符串库。
#include <string>
// 包含std::make_pair。
#include <utility>

int main() {
  // std::unordered_map是一个包含具有唯一键的键值对的数据结构。
  // 本质上，这意味着你可以在代码中将其用作哈希表。

  // 你可以用以下语法声明一个具有字符串键和int值的unordered_map。
  std::unordered_map<std::string, int> map;

  // insert函数用于向unordered map中插入项目。
  map.insert({"foo", 2});

  // insert函数也接受std::pair作为参数。
  // std::pair是一个通用的对类型，
  // 你可以通过调用带2个参数的std::make_pair来创建一个。
  // std::make_pair在头文件<utility>中定义，
  // 并构造通用对类型的实例。
  map.insert(std::make_pair("jignesh", 445));

  // 你也可以通过传递对的初始化列表来一次插入多个元素。
  map.insert({{"spam", 1}, {"eggs", 2}, {"garlic rice", 3}});

  // 也可以通过数组风格的语法插入元素，
  // 即使元素之前不存在。
  map["bacon"] = 5;

  // 你也可以使用相同的语法更新unordered map中的元素。
  map["spam"] = 15;

  // find函数用于在unordered map中查找元素。
  // 如果元素存在，它返回指向找到元素的迭代器，
  // 否则返回指向unordered map容器末尾的迭代器。
  std::unordered_map<std::string, int>::iterator result = map.find("jignesh");
  if (result != map.end()) {
    // 这是从迭代器访问键/值对的一种方法。
    std::cout << "Found key " << result->first << " with value "
              << result->second << std::endl;

    // 解引用迭代器是从迭代器访问键/值对的另一种方法。
    std::pair<std::string, int> pair = *result;
    std::cout << "DEREF: Found key " << pair.first << " with value "
              << pair.second << std::endl;
  }

  // count函数返回unordered map中具有指定键的元素数量。
  size_t count = map.count("spam");
  if (count == 1) {
    std::cout
        << "A key-value pair with key spam exists in the unordered map.\n";
  }

  // erase函数从unordered map中删除值。
  // 它可以接受一个键作为参数。
  map.erase("eggs");

  // 我们确认eggs/2键值对不再在map中了。
  if (map.count("eggs") == 0) {
    std::cout << "Key-value pair with key eggs does not exist in the unordered "
                 "map.\n";
  }

  // 另外，如果我们想删除某个位置的元素，
  // 我们可以向erase函数传递一个迭代器。
  // 以下代码将删除键为"garlic rice"的键值对。
  // 注意std::next是一个迭代器函数，
  // 返回作为其参数传入的迭代器的后继。
  map.erase(map.find("garlic rice"));

  // 我们确认garlic rice/3键值对不再在map中了。
  if (map.count("garlic rice") == 0) {
    std::cout << "Key-value pair with key garlic rice does not exist in the "
                 "unordered map.\n";
  }

  // 我们可以通过unordered map迭代器遍历unordered map元素。
  // 你不能通过任何种类的索引遍历unordered map。
  std::cout << "Printing the elements of the iterator:\n";
  for (std::unordered_map<std::string, int>::iterator it = map.begin();
       it != map.end(); ++it) {
    // 我们可以通过解引用迭代器来访问元素本身。
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }
  std::cout << "\n";

  // 就像std::vector一样，
  // 我们也可以通过for-each循环遍历unordered map。
  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const std::pair<const std::string, int> &elem : map) {
    std::cout << "(" << elem.first << ", " << elem.second << "), ";
  }
  std::cout << "\n";

  // 我们在auto.cpp中讨论了遍历C++ STL容器的更具风格和可读性的方法！
  // 如果你感兴趣的话可以查看一下。

  return 0;
}