// Copyright 2026 Khaferl Pavel

#ifndef LIB_STACK_ON_MASS_STACK_ON_MASS_H_
#define LIB_STACK_ON_MASS_STACK_ON_MASS_H_

#include <cstddef>
#include <stdexcept>

template <typename T>
class TStack {
 private:
  T* _data;
  size_t _size;
  int _top;

 public:
  explicit TStack(size_t);
  TStack(const TStack&);
  ~TStack();

  void push(const T&);
  T pop();
  inline T& top();
  inline size_t size() const noexcept;
  inline size_t count() const noexcept;
  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
};

template <typename T>
TStack<T>::TStack(size_t size) {
  _data = new T[size];
  _size = size;
  _top = -1;
}

template <typename T>
TStack<T>::TStack(const TStack& other) {
  _data = new T[other._size];
  for (size_t i = 0; i < other._size; i++) {
    _data[i] = other._data[i];
  }
  _size = other._size;
  _top = other._top;
}

template <typename T>
TStack<T>::~TStack() {
  delete[] _data;
}

template <typename T>
inline bool TStack<T>::is_empty() const noexcept {
  return (_top == -1);
}

template <typename T>
inline bool TStack<T>::is_full() const noexcept {
  return (_top == _size - 1);
}

template <typename T>
inline size_t TStack<T>::size() const noexcept {
  return _size;
}

template <typename T>
inline size_t TStack<T>::count() const noexcept {
    return _top + 1;
}

template <typename T>
inline T& TStack<T>::top() {
  return _data[_top];
}

template <typename T>
T TStack<T>::pop() {
  if (is_empty()) {
    throw std::logic_error("stack is empty");
  }
  return _data[_top--];
}

template <typename T>
void TStack<T>::push(const T& value) {
  if (is_full()) {
      throw std::logic_error("stack is full");
  }
  _data[++_top] = value;
}

#endif  // LIB_STACK_ON_MASS_STACK_ON_MASS_H_
