// 虽然C++没有特定的读者-写者锁库，
// 但可以通过使用std::shared_mutex、std::shared_lock和std::unique_lock库来模拟一个。
// 这个程序展示了如何做到这一点的小例子。

// std::shared_mutex是一个允许共享只读锁定和独占只写锁定的互斥锁。
// std::shared_lock可以用作RAII风格的读锁，
// std::unique_lock可以用作RAII风格的写锁。
// scoped_lock.cpp讨论了C++中的RAII风格锁定。

// 如果你想复习读者-写者锁和读者-写者问题的概念，
// 可以参考15-213/513/613的幻灯片：
// https://www.cs.cmu.edu/afs/cs/academic/class/15213-s23/www/lectures/25-sync-advanced.pdf

// 包含std::cout（打印）用于演示目的。
#include <iostream>
// 包含mutex库头文件。
#include <mutex>
// 包含shared mutex库头文件。
#include <shared_mutex>
// 包含thread库头文件。
#include <thread>

// 定义一个全局count变量和一个供所有线程使用的shared mutex。
// std::shared_mutex是一个允许共享锁定以及独占锁定的互斥锁。
int count = 0;
std::shared_mutex m;

// 这个函数使用std::shared_lock（读锁等价物）来获得对count变量的只读共享访问，
// 并读取count变量。
void read_value() {
  std::shared_lock lk(m);
  std::cout << "Reading value " + std::to_string(count) + "\n" << std::flush;
}

// 这个函数使用std::unique_lock（写锁等价物）来获得对count变量的独占访问并写入值。
void write_value() {
  std::unique_lock lk(m);
  count += 3;
}

// main方法构造六个thread对象，让其中两个运行write_value函数，
// 四个运行read_value函数，全部并行执行。
// 这意味着输出是不确定的，
// 取决于哪些线程首先获得锁。
// 多运行几次程序，看看你是否能得到不同的输出。
int main() {
  std::thread t1(read_value);
  std::thread t2(write_value);
  std::thread t3(read_value);
  std::thread t4(read_value);
  std::thread t5(write_value);
  std::thread t6(read_value);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();

  return 0;
}