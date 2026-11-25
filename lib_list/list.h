// Copyright 2026 Khaferl Pavel

#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

// Default arguments for a member function of a class template shall be
// specified on the initial declaration of the member function within
// the class template.
template <typename T>
class List {
 private:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T&, Node* = nullptr);
    Node(const Node&);
    Node(Node&&) noexcept;
    ~Node() = default;
  };

  template <typename Type>
  class Iterator {
   private:
    Node* cur;
    friend class List<T>;
    template <typename>
    friend class Iterator;

   public:
    explicit Iterator(Node* c = nullptr) noexcept : cur(c) {}
    Iterator(const Iterator&) noexcept = default;
    Iterator& operator=(const Iterator&) noexcept = default;

    Type& operator*() const {
      if (cur == nullptr) {
        throw std::logic_error("its not safe to use * for nullptr");
      }
      return cur->data;
    }

    Type* operator->() const {
      if (cur == nullptr) {
        throw std::logic_error("its not safe to use -> for nullptr");
      }
      return &(cur->data);
    }

    Iterator& operator++() noexcept {
      if (cur != nullptr) {
        cur = cur->next;
      }
      return *this;
    }

    Iterator operator++(int) noexcept {
      Iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    Iterator operator+(int i) const {
      if (i < 0) {
        throw std::logic_error("i value shall be positive");
      }
      Iterator tmp(*this);
      while (i > 0) {
        if (tmp.cur == nullptr) {
          throw std::logic_error("nullptr");
        }
        tmp.cur = tmp.cur->next;
        --i;
      }
      return tmp;
    }

    Iterator& operator+=(int i) {
      *this = *this + i;
      return *this;
    }

    bool operator==(const Iterator& other) const noexcept {
      return cur == other.cur;
    }

    bool operator!=(const Iterator& other) const noexcept {
      return cur != other.cur;
    }
  };

  size_t size;
  Node* head;
  Node* tail;

 public:
  using iterator = Iterator<T>;
  using const_iterator = Iterator<const T>;

  List();
  List(const List& other);
  List(List&&) noexcept;
  ~List();

  List& operator=(const List&);
  List& operator=(List&&) noexcept;

  void push_front(const T&);
  void push_back(const T&);
  Node* insert(const T&, Node*);
  Node* insert(const T&, size_t);
  Node* find(const T&);
  T pop_front();
  T pop_back();
  T erase(Node*);
  T erase(size_t);
  bool is_empty() const noexcept;
  size_t get_size() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
};

template <typename T>
size_t List<T>::get_size() const noexcept {
  return size;
}

// Need to use initializer list here otherwise -> error.
// With init list data creates instantly with right values.
template <typename T>
List<T>::Node::Node(const T& d, Node* n) : data(d), next(n) {}

// useless?
template <typename T>
List<T>::Node::Node(const Node& other) : data(other.data), next(nullptr) {}

template <typename T>
List<T>::Node::Node(Node&& other) noexcept
    : data(std::move(other.data)), next(other.next) {
  other.next = nullptr;
}

template <typename T>
List<T>::List() : size(0), head(nullptr), tail(nullptr) {}

template <typename T>
List<T>::List(const List& other) : size(0), head(nullptr), tail(nullptr) {
  if (other.head == nullptr) {
    return;
  }
  head = new Node(other.head->data);
  Node* current_for_this = head;
  Node* current_for_other = other.head;
  while (current_for_other->next != nullptr) {
    Node* new_node = new Node(current_for_other->next->data);
    current_for_this->next = new_node;
    current_for_this = current_for_this->next;
    current_for_other = current_for_other->next;
  }
  tail = current_for_this;
  size = other.size;
}

template <typename T>
List<T>::List(List&& other) noexcept
    : size(other.size), head(other.head), tail(other.tail) {
  other.size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template <typename T>
List<T>::~List() {
  Node* current = head;
  while (current != nullptr) {
    Node* next_current = current->next;
    delete current;
    current = next_current;
  }
  size = 0;
  head = nullptr;
  tail = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
  if (this == &other) {
    return (*this);
  }
  List cpy_of_other(other);
  std::swap(size, cpy_of_other.size);
  std::swap(head, cpy_of_other.head);
  std::swap(tail, cpy_of_other.tail);
  return (*this);
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
  std::swap(size, other.size);
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  return (*this);
}

// head == nullptr?
template <typename T>
bool List<T>::is_empty() const noexcept {
  return (size == 0);
}

template <typename T>
void List<T>::push_front(const T& value) {
  if (is_empty()) {
    head = new Node(value);
    tail = head;
    size++;
    return;
  }
  Node* new_node = new Node(value, head);
  head = new_node;
  size++;
}

template <typename T>
void List<T>::push_back(const T& value) {
  if (is_empty()) {
    head = new Node(value);
    tail = head;
    size++;
    return;
  }
  tail->next = new Node(value);
  tail = tail->next;
  size++;
}

template <typename T>
T List<T>::pop_front() {
  if (is_empty()) {
    throw std::invalid_argument("empty");
  }
  T copy = head->data;
  Node* prev_head = head;
  head = head->next;
  delete prev_head;
  if (size == 1) {
    tail = nullptr;
  }
  size--;
  return copy;
}

template <typename T>
T List<T>::pop_back() {
  if (is_empty()) {
    throw std::invalid_argument("empty");
  }
  T copy = tail->data;
  if (size == 1) {
    delete tail;
    head = nullptr;
    tail = nullptr;
    size--;
    return copy;
  }
  Node* prev_tail = head;
  while (prev_tail->next != tail) {
    prev_tail = prev_tail->next;
  }
  prev_tail->next = nullptr;
  delete tail;
  tail = prev_tail;
  size--;
  return copy;
}

template <typename T>
typename List<T>::Node* List<T>::find(const T& value) {
  Node* current = head;
  while (current != nullptr) {
    if (current->data == value) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

template <typename T>
typename List<T>::Node* List<T>::insert(const T& value, Node* pos) {
  if (pos == nullptr) {
    throw std::invalid_argument("nullptr");
  }
  if (pos == head) {
    push_front(value);
    return head;
  }
  Node* current = head;
  while (current != nullptr && current->next != pos) {
    current = current->next;
  }
  if (current == nullptr) {
    throw std::invalid_argument("node not found");
  }
  Node* new_node = new Node(value, pos);
  current->next = new_node;
  size++;
  return new_node;
}

template <typename T>
typename List<T>::Node* List<T>::insert(const T& value, size_t index) {
  if (index > size) {
    throw std::out_of_range("out of size");
  }
  if (index == 0) {
    push_front(value);
    return head;
  }
  if (index == size) {
    push_back(value);
    return tail;
  }
  Node* current_on_index = head;
  for (size_t i = 0; i < index; i++) {
    current_on_index = current_on_index->next;
  }
  return insert(value, current_on_index);
}

template <typename T>
T List<T>::erase(Node* pos) {
  if (pos == nullptr) {
    throw std::invalid_argument("nullptr");
  }
  if (pos == head) {
    return pop_front();
  }
  if (pos == tail) {
    return pop_back();
  }
  Node* current = head;
  while (current != nullptr && current->next != pos) {
    current = current->next;
  }
  if (current == nullptr) {
    throw std::invalid_argument("node not found");
  }
  T copy = pos->data;
  current->next = pos->next;
  delete pos;
  size--;
  return copy;
}

template <typename T>
T List<T>::erase(size_t index) {
  if (index >= size) {
    throw std::out_of_range("out of size");
  }
  if (index == 0) {
    return pop_front();
  }
  Node* current_on_index = head;
  for (size_t i = 0; i < index; i++) {
    current_on_index = current_on_index->next;
  }
  return erase(current_on_index);
}

template <typename T>
typename List<T>::iterator List<T>::begin() noexcept {
  return iterator(head);
}

template <typename T>
typename List<T>::iterator List<T>::end() noexcept {
  return iterator(nullptr);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const noexcept {
  return const_iterator(head);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const noexcept {
  return const_iterator(nullptr);
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const noexcept {
  return const_iterator(head);
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const noexcept {
  return const_iterator(nullptr);
}

#endif  // LIB_LIST_LIST_H_
