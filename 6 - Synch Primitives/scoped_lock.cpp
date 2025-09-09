// 这个程序提供了一个使用 std::scoped_lock 的小例子。
// std::scoped_lock 是一个互斥锁包装类，
// 提供了一种 RAII 风格的获取和释放锁的方法。
// 这意味着当对象被构造时，锁被获取，
// 当对象被析构时，锁被释放。

// 包含 std::cout（用于打印）以进行演示。
#include <iostream>
// 包含互斥锁库头文件。
#include <mutex>
// 包含线程库头文件。
#include <thread>

// 定义一个全局计数变量和两个互斥锁，供两个线程使用。
int count = 0;
std::mutex m;

// add_count 函数允许线程原子地将计数变量增加 1。
void add_count() {
  // std::scoped_lock 的构造函数允许线程获取互斥锁 m。
  std::scoped_lock slk(m);
  count += 1;

  // 一旦函数 add_count 结束，对象 slk 超出作用域，
  // 在其析构函数中，互斥锁 m 被释放。
}

// main 方法与 mutex.cpp 中的相同。
// 它构造线程对象，在两个线程上运行 add_count，
// 并在执行后打印 count 的结果。
int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}