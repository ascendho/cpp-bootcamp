## Condition Variable

- `std::condition_variable` is a standard library synchronization primitive introduced in C++11. It implements the **condition variable** mechanism — an important multithreaded synchronization primitive that allows threads to wait until a specific condition is met, at which point other threads can notify the waiting threads to recheck the condition.
- `notify_one()` is a core member function of `std::condition_variable`, used to **wake up one** thread waiting on the condition variable.

> `notify_one()` is used for task distribution, ensuring each task is processed by only one worker thread, while `notify_all()` is used for shutdown signals, ensuring all threads receive the exit notification.

- `unique_lock` is a **flexible and powerful mutex wrapper** introduced in C++11 — a movable but non-copyable RAII-style lock manager.

> Note: `unique_lock` **works with condition variables** (this is a key difference from `lock_guard`).

- `wait` is the core member function of `std::condition_variable`, used to make a thread **wait for a certain condition to become true**.
