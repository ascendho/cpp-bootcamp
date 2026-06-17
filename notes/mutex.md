## Mutex

- `mutex` is a mutual exclusion lock provided by the C++ standard library for synchronization in multithreaded programming. Its primary role is to protect access to shared resources, preventing multiple threads from simultaneously modifying the same data and causing race conditions. Key characteristics:

1. **Mutual exclusion**: only one thread can hold the lock at a time; other threads must wait for the lock to be released before executing the critical section.
2. **Thread safety**: the locking mechanism enables safe access to shared data, preventing corruption or inconsistency.
3. **Simple interface**: main methods are `.lock()`, `.unlock()`, `.try_lock()`.

> `lock()`: acquires the lock; blocks the thread if the lock is already held.
>
> `unlock()`: releases the lock, allowing other threads to acquire it.
>
> `try_lock()`: attempts to acquire the lock without blocking; returns true/false.

- `std::thread` is the **thread class** provided by the C++11 standard library for creating and managing new threads in a program, enabling concurrent execution of multiple tasks.

> `join()`: makes the main thread wait for the child thread to complete.
>
> `detach()`: detaches the child thread from the main thread; the child runs in the background.
>
> Note: every `std::thread` must be either `join()`ed or `detach()`ed, otherwise the program will terminate abnormally.

- The main thread is the program's entry point — the thread executing the `main()` function. It is automatically created by the operating system at program startup and is responsible for initialization and scheduling other threads.
- In `mutex.cpp`, both `t1` and `t2` are child threads.
