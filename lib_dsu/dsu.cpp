#include "lib_dsu/dsu.h"

// [1; N]
// 1 2 3 4 5 6 7 8 9
// 0 1 2 3 4 5 6 7 8
size_t DSU::get_size() const noexcept {
  return size;
}

DSU::DSU(size_t s) {
  size = s;
  parent = new size_t[size];
  for (size_t i = 0; i < s; i++) {
	parent[i] = i + 1;
  }
  rank = new size_t[size];
  for (size_t i = 0; i < s; i++) {
	rank[i] = 0;
  }
}

// risky move
DSU::~DSU() noexcept {
  delete[] parent;
  delete[] rank;
  size = 0;
}

// make +1 method for returning rank for exact member???
size_t DSU::find(size_t element) {
  if (element > size || element == 0) {
	throw std::out_of_range("out of size");
  }
  if (element == parent[element - 1]) {
	return element;
  }
  size_t true_parent = find(parent[element - 1] + 1);
  parent[element - 1] = true_parent - 1;
  return true_parent;
}

void DSU::uni(size_t first, size_t second) {

}