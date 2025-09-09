// 这个程序展示了std::mutex使用的一个小例子。
// std::mutex类提供了互斥锁同步原语。

// 包含std::cout（打印）用于演示目的。
#include <iostream>
// 包含mutex库头文件。
#include <mutex>
// 包含thread库头文件。
#include <thread>

// 定义一个全局count变量和一个供两个线程使用的mutex。
int count = 0;

// 这是声明和默认初始化mutex的语法。
std::mutex m;

// add_count函数允许线程原子地将count变量增加1。
void add_count() {
  // 在访问共享资源count之前获取锁。
  m.lock();
  count += 1;
  // 在访问共享资源count之后释放锁。
  m.unlock();
}

// main方法构造两个thread对象，
// 并让它们并行运行add_count函数。
// 这些线程执行完毕后，我们打印count值，
// 显示两个增量操作都成功工作了。
// std::thread库是用于构造线程的C++ STL库。
// 你可以将其视为C中pthread库的C++等价物。
int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}