## Read-Write Lock

- `std::shared_mutex` is a special mutex introduced in C++14 that allows:

  > **Multiple threads to simultaneously acquire a shared lock** (read lock);
  > **Only one thread to acquire an exclusive lock** (write lock);
  > **Shared locks and exclusive locks are mutually exclusive**.
