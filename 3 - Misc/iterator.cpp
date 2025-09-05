// C++ 迭代器是指向容器内部元素的对象。
// 它们可以用来遍历该容器的对象。
// 你知道的一个迭代器的例子是指针。
// 指针可以用来遍历 C 风格数组。
// 看下面的C 风格代码片段：
// int *array = malloc(sizeof(int) * 10);
// int *iter = array;
// int zero_elem = *iter;
// iter++;
// int first_elem = *iter;
// 如我们所见，++ 操作符可以用来遍历 C 风格数组，
// 解引用操作符返回迭代器处的值。

// C++ 迭代器的主要组件是它的两个主要操作符。
// 迭代器上的解引用操作符（*）应该返回迭代器当前位置元素的值。
// ++（后缀递增）操作符应该将迭代器的位置递增 1。
// 如你所见，这对于用指针遍历 C 风格数组是成立的。

// 在 vectors.cpp、sets.cpp、unordered_maps.cpp 和 auto.cpp 中有一些
// 关于如何使用迭代器访问 C++ STL 容器中元素的例子。
// 这是因为在 C++ 中使用迭代器访问和修改 C++ STL 容器中的元素被认为是良好的风格，
// 值得在这些文件中提及。

// 这个文件将主要关注迭代器的实现。
// 在这个文件中，
// 我们通过编写一个基本的双向链表（DLL）迭代器来演示实现 C++ 迭代器。

// 包含 std::cout（用于打印）以进行演示。
#include <iostream>

// 这是 Node 结构体的定义，
// 用于我们的双向链表。
struct Node {
  Node(int val) 
    : next_(nullptr)
    , prev_(nullptr)
    , value_(val) {}

  Node* next_;
  Node* prev_;
  int value_;
};

// 这个类为双向链表类 DLL 实现了 C++ 风格的迭代器。
// 这个类的构造函数接受一个标记迭代开始的节点。
// 它还实现了几个操作符，
// 用于递增迭代器（即访问 DLL 中的下一个元素）
// 并通过比较它们的 curr_ 指针来测试两个不同迭代器之间的相等性。
class DLLIterator {
  public:
    DLLIterator(Node* head) 
      : curr_(head) {}

    // 实现前缀递增操作符（++iter）。
    DLLIterator& operator++() {
      curr_ = curr_->next_;
      return *this;
    }

    // 实现后缀递增操作符（iter++）。
    // 前缀和后缀递增操作符之间的区别是操作符的返回值。
    // 前缀操作符返回递增的结果，
    // 而后缀操作符返回递增前的迭代器。
    DLLIterator operator++(int) {
      DLLIterator temp = *this;
      ++*this;
      return temp;
    }

    // 这是 DLLIterator 类的相等操作符。
    // 它测试当前指针是否相同。
    bool operator==(const DLLIterator &itr) const {
      return itr.curr_ == this->curr_;
    }

    // 这是 DLLIterator 类的不等操作符。
    // 它测试当前指针是否不相同。
    bool operator!=(const DLLIterator &itr) const {
      return itr.curr_ != this->curr_;
    }

    // 这是 DLLIterator 类的解引用操作符。
    // 它返回迭代器当前位置元素的值。
    // 迭代器的当前位置由 curr_ 标记，
    // 我们可以通过访问其 value 字段来访问 curr_ 的值。
    int operator*() {
      return curr_->value_;
    }

  private:
    Node* curr_;
};

// 这是双向链表的基本实现。
// 它还包括迭代器函数 Begin 和 End，
// 它们返回可用于遍历此 DLL 实例的 DLLIterator。
class DLL {
  public:
    // DLL 类构造函数。
    DLL() 
    : head_(nullptr)
    , size_(0) {}

    // 析构函数应该通过遍历删除所有节点。
    ~DLL() {
      Node *current = head_;
      while(current != nullptr) {
        Node *next = current->next_;
        delete current;
        current = next;
      }
      head_ = nullptr;
    }

    // 在 DLL 头部插入 val 的函数。
    void InsertAtHead(int val) {
      Node *new_node = new Node(val);
      new_node->next_ = head_;

      if (head_ != nullptr) {
        head_->prev_ = new_node;
      }

      head_ = new_node;
      size_ += 1;
    }

    // Begin() 函数返回指向 DLL 头部的迭代器，
    // 这是遍历时要访问的第一个元素。
    DLLIterator Begin() {
      return DLLIterator(head_);
    }

    // End() 函数返回标记迭代器最后一个元素之后位置的迭代器。
    // 在这种情况下，这将是一个当前指针设置为 nullptr 的迭代器。
    DLLIterator End() {
      return DLLIterator(nullptr);
    }

    Node* head_{nullptr};
    size_t size_;
};

// main 函数展示了 DLL 迭代器的用法。
int main() {
  // 创建一个 DLL 并向其中插入元素。
  DLL dll;
  dll.InsertAtHead(6);
  dll.InsertAtHead(5);
  dll.InsertAtHead(4);
  dll.InsertAtHead(3);
  dll.InsertAtHead(2);
  dll.InsertAtHead(1);

  // 我们可以通过前缀和后缀操作符遍历我们的 DLL。
  std::cout << "Printing elements of the DLL dll via prefix increment operator\n";
  for (DLLIterator iter = dll.Begin(); iter != dll.End(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  std::cout << "Printing elements of the DLL dll via postfix increment operator\n";
  for (DLLIterator iter = dll.Begin(); iter != dll.End(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  return 0;
}