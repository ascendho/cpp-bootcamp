## Scoped Lock

- `std::scoped_lock` is a C++17 RAII (Resource Acquisition Is Initialization) style mutex wrapper class.

> **RAII principles:**
>
> - **Initialize on resource acquisition**: automatically acquires the lock during object construction.
> - **Release on destruction**: automatically releases the lock during object destruction.
> - **Exception safety**: the destructor ensures the lock is released even if an exception occurs.

- Comparison with other locks:

| Lock Type           | Characteristics                        | Use Case                          |
| ------------------- | -------------------------------------- | --------------------------------- |
| `std::lock_guard`   | Simple RAII, single lock               | Basic mutual exclusion            |
| `std::unique_lock`  | Flexible, supports deferred locking, condition variables | When manual lock timing is needed |
| `std::scoped_lock`  | RAII, supports multiple locks, deadlock avoidance | **Recommended for modern C++**    |
