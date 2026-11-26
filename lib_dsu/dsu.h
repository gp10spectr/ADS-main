#include <cstddef>
#include <iostream>

// [1; N]
// 1 2 3 4 5 6 7 8 9
// 0 1 2 3 4 5 6 7 8
class DSU {
private:
  size_t* parent;
  size_t size;
  size_t* rank;
public:
  DSU(size_t);
  ~DSU() noexcept;

  void uni(size_t, size_t);
  size_t find(size_t);
  size_t get_size() const noexcept;

};