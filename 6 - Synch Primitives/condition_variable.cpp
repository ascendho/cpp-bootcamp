// 这个程序展示了std::condition_variable使用的一个小例子。
// std::condition_variable类提供了条件变量同步原语。
// 条件变量原语允许线程在获取互斥锁之前等待特定条件。
// 它还允许其他线程向等待线程发出信号，提醒它们条件可能为真。

// 有关C风格条件变量的更详细介绍，请参见
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf。

// 这个程序运行三个线程。
// 其中两个线程运行一个函数，该函数原子地将全局count变量增加1，
// 并在count变量为2时通知等待线程。
// 当count变量为2时，等待线程唤醒，获取锁，并打印count值。

// 包含条件变量库头文件。
#include <condition_variable>
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// 包含mutex库头文件。
#include <mutex>
// 包含thread库头文件。
#include <thread>

// 定义一个全局count变量、一个mutex和一个条件变量供两个线程使用。
int count = 0;
std::mutex m;

// 这是声明和默认初始化条件变量的语法。
std::condition_variable cv;

// 在这个函数中，线程将count变量增加1。
// 如果count值为2，它也会通知一个等待线程。
// 它由main函数中的两个线程运行。
void add_count_and_notify() {
  std::scoped_lock slk(m);
  count += 1;
  if (count == 2) {
    cv.notify_one();
  }
}

// 这个函数由等待线程运行，等待条件count == 2。
// 之后，它获取互斥锁m并在临界区执行代码。
// 条件变量需要构造一个std::unique_lock对象。
// std::unique_lock是一种C++ STL同步原语类型，
// 提供更多灵活性和功能，包括与条件变量一起使用。
// 特别地，它是可移动的，但不可复制构造或复制赋值。
void waiter_thread() {
  std::unique_lock lk(m);
  cv.wait(lk, []{return count == 2;});

  std::cout << "Printing count: " << count << std::endl;
}

// main方法构造三个thread对象，
// 并让其中两个并行运行add_count_and_notify函数。
// 这些线程执行完毕后，我们从等待线程打印count值，
// 显示两个增量操作以及等待线程中的条件获取都成功工作了。
int main() {
  std::thread t1(add_count_and_notify);
  std::thread t2(add_count_and_notify);
  std::thread t3(waiter_thread);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}