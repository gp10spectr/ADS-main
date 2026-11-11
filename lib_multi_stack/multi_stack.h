// Copyright 2026 Khaferl Pavel

#ifndef LIB_MULTI_STACK_MULTI_STACK_H_
#define LIB_MULTI_STACK_MULTI_STACK_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Multi_Stack {
 private:
  T* data;
  size_t N;
  size_t size;
  size_t* lv;
  size_t* rv;
  size_t* tops;
  size_t count;
  // size?

  void repack();

 public:
  Multi_Stack(size_t, size_t);  // N, size
  // Multi_Stack(size_t);       // try?
  Multi_Stack(const Multi_Stack&);
  Multi_Stack(Multi_Stack&&) noexcept;
  ~Multi_Stack();

  size_t get_size() const noexcept;
  size_t get_stack_count() const noexcept;
  size_t get_count() const noexcept;
  T& get_top(size_t);
  void push(size_t, const T&);
  T pop(size_t);
  bool is_full() const noexcept;
  bool is_empty() const noexcept;
  bool is_empty(size_t) const;
  bool is_full(size_t) const;
  Multi_Stack& operator=(const Multi_Stack&);
  Multi_Stack& operator=(Multi_Stack&&) noexcept;
};

template <typename T>
Multi_Stack<T>::Multi_Stack(size_t stack_count, size_t s) {
  if (stack_count == 0 || s < stack_count) {
    throw std::invalid_argument("invalid size or count");
  }
  N = stack_count;
  size = s;
  count = 0;
  data = new T[s];
  lv = new size_t[N];
  rv = new size_t[N];
  tops = new size_t[N];

  size_t step = size / N;
  size_t rem = size % N;
  size_t cur = 0;
  for (size_t i = 0; i < N; i++) {
    lv[i] = cur;
    size_t allocated = step + (i < rem ? 1 : 0);
    rv[i] = lv[i] + allocated;
    tops[i] = lv[i];
    cur = rv[i];
  }
}

template <typename T>
Multi_Stack<T>::Multi_Stack(const Multi_Stack& other) {
  size = other.size;
  N = other.N;
  count = other.count;
  data = new T[size];
  lv = new size_t[N];
  rv = new size_t[N];
  tops = new size_t[N];
  for (size_t i = 0; i < size; i++) {
    data[i] = other.data[i];
  }
  for (size_t i = 0; i < N; i++) {
    lv[i] = other.lv[i];
    rv[i] = other.rv[i];
    tops[i] = other.tops[i];
  }
}

template <typename T>
Multi_Stack<T>::Multi_Stack(Multi_Stack&& other) noexcept
    : data(other.data),
      N(other.N),
      size(other.size),
      lv(other.lv),
      rv(other.rv),
      tops(other.tops),
      count(other.count) {
  other.data = nullptr;
  other.lv = nullptr;
  other.rv = nullptr;
  other.tops = nullptr;
  other.size = 0;
  other.N = 0;
  other.count = 0;
}

template <typename T>
Multi_Stack<T>::~Multi_Stack() {
  delete[] data;
  delete[] lv;
  delete[] rv;
  delete[] tops;
  data = nullptr;
  lv = nullptr;
  rv = nullptr;
  tops = nullptr;
  size = 0;
  N = 0;
  count = 0;
}

template <typename T>
Multi_Stack<T>& Multi_Stack<T>::operator=(const Multi_Stack& other) {
  if (this == &other) {
    return *this;
  }
  Multi_Stack tmp(other);
  std::swap(data, tmp.data);
  std::swap(N, tmp.N);
  std::swap(size, tmp.size);
  std::swap(lv, tmp.lv);
  std::swap(rv, tmp.rv);
  std::swap(tops, tmp.tops);
  std::swap(count, tmp.count);
  return *this;
}

template <typename T>
Multi_Stack<T>& Multi_Stack<T>::operator=(Multi_Stack&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  delete[] data;
  delete[] lv;
  delete[] rv;
  delete[] tops;
  data = other.data;
  N = other.N;
  size = other.size;
  lv = other.lv;
  rv = other.rv;
  tops = other.tops;
  count = other.count;
  other.data = nullptr;
  other.lv = nullptr;
  other.rv = nullptr;
  other.tops = nullptr;
  other.size = 0;
  other.N = 0;
  other.count = 0;
  return *this;
}

template <typename T>
size_t Multi_Stack<T>::get_size() const noexcept {
  return size;
}

template <typename T>
size_t Multi_Stack<T>::get_stack_count() const noexcept {
  return N;
}

template <typename T>
size_t Multi_Stack<T>::get_count() const noexcept {
  return count;
}

template <typename T>
T& Multi_Stack<T>::get_top(size_t stack_count) {
  if (stack_count >= N) {
    throw std::out_of_range("out of range");
  }
  if (is_empty(stack_count)) {
    throw std::out_of_range("empty");
  }
  return data[tops[stack_count] - 1];
}

template <typename T>
void Multi_Stack<T>::push(size_t stack_count, const T& value) {
  if (stack_count >= N) {
    throw std::out_of_range("out of range");
  }
  if (is_full()) {
    throw std::out_of_range("full");
  }
  if (is_full(stack_count)) {
    repack();
  }
  data[tops[stack_count]] = value;
  tops[stack_count]++;
  count++;
}

template <typename T>
T Multi_Stack<T>::pop(size_t stack_count) {
  if (stack_count >= N) {
    throw std::out_of_range("out of range");
  }
  if (is_empty(stack_count)) {
    throw std::out_of_range("empty");
  }
  tops[stack_count]--;
  count--;
  return data[tops[stack_count]];
}

template <typename T>
bool Multi_Stack<T>::is_full() const noexcept {
  return (count == size);
}

template <typename T>
bool Multi_Stack<T>::is_empty() const noexcept {
  return (count == 0);
}

template <typename T>
bool Multi_Stack<T>::is_full(size_t stack_idx) const {
  if (stack_idx >= N) {
    throw std::out_of_range("out of range");
  }
  return tops[stack_idx] == rv[stack_idx];
}

template <typename T>
bool Multi_Stack<T>::is_empty(size_t stack_idx) const {
  if (stack_idx >= N) {
    throw std::out_of_range("out of range");
  }
  return tops[stack_idx] == lv[stack_idx];
}

template <typename T>
void Multi_Stack<T>::repack() {
  if (is_full()) {
    return;
  }
  size_t free_space = size - count;
  size_t* new_cap = new size_t[N];
  for (size_t i = 0; i < N; i++) {
    new_cap[i] = tops[i] - lv[i];
  }
  for (size_t i = 0; i < N && free_space > 0; i++) {
    if (tops[i] == rv[i]) {
      new_cap[i]++;
      free_space--;
    }
  }
  size_t base_add = free_space / N;
  size_t rem = free_space % N;
  for (size_t i = 0; i < N; i++) {
    new_cap[i] += base_add + (i < rem ? 1 : 0);
  }
  T* new_data = new T[size];
  size_t current_pos = 0;
  for (size_t i = 0; i < N; i++) {
    size_t current_len = tops[i] - lv[i];
    for (size_t j = 0; j < current_len; j++) {
      new_data[current_pos + j] = std::move(data[lv[i] + j]);
    }
    lv[i] = current_pos;
    tops[i] = current_pos + current_len;
    current_pos += new_cap[i];
    rv[i] = current_pos;
  }
  delete[] new_cap;
  delete[] data;
  data = new_data;
}

#endif  // LIB_MULTI_STACK_MULTI_STACK_H_
