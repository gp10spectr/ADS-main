// Copyright 2026 Khaferl Pavel

#ifndef LIB_LIST_DOUBLE_LIST_H_
#define LIB_LIST_DOUBLE_LIST_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Double_List {
 private:
  struct Node {
    T data;
    Node* next;
    Node* previous;

    explicit Node(const T& d, Node* n = nullptr, Node* p = nullptr);
    // useless?
    // Node(const Node&) = default;
    // Node(Node&&) noexcept = default;
    ~Node() = default;
  };

  size_t size;
  Node* head;
  Node* tail;

 public:
  Double_List();
  Double_List(const Double_List&);
  Double_List(Double_List&&) noexcept;
  ~Double_List();

  Double_List& operator=(const Double_List&);
  Double_List& operator=(Double_List&&) noexcept;

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
};

template <typename T>
size_t Double_List<T>::get_size() const noexcept {
  return size;
}

template <typename T>
Double_List<T>::Node::Node(const T& d, Node* n, Node* p) : data(d), next(n), previous(p) {}

template <typename T>
Double_List<T>::Double_List() : size(0), head(nullptr), tail(nullptr) {}

template <typename T>
Double_List<T>::Double_List(const Double_List& other) : size(0), head(nullptr), tail(nullptr) {
  if (other.size == 0) {
    return;
  }
  head = new Node(other.head->data);
  Node* current_for_this = head;
  Node* current_for_other = other.head;
  while (current_for_other->next != nullptr) {
    Node* new_node = new Node(current_for_other->next->data, nullptr, current_for_this);
    current_for_this->next = new_node;
    current_for_this = current_for_this->next;
    current_for_other = current_for_other->next;
  }
  tail = current_for_this;
  size = other.size;
}

template <typename T>
Double_List<T>::Double_List(Double_List&& other) noexcept : size(other.size), head(other.head), tail(other.tail) {
  other.size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template <typename T>
Double_List<T>::~Double_List() {
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
Double_List<T>& Double_List<T>::operator=(const Double_List& other) {
  if (this == &other) {
    return (*this);
  }
  Double_List copy_of_other(other);
  std::swap(size, copy_of_other.size);
  std::swap(head, copy_of_other.head);
  std::swap(tail, copy_of_other.tail);
  return (*this);
}

template <typename T>
Double_List<T>& Double_List<T>::operator=(Double_List&& other) noexcept {
  std::swap(size, other.size);
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  return (*this);
}

template <typename T>
bool Double_List<T>::is_empty() const noexcept {
  return (size == 0);
}

template <typename T>
void Double_List<T>::push_front(const T& value) {
  if (is_empty()) {
    head = new Node(value);
    tail = head;
    size++;
    return;
  }
  Node* new_node = new Node(value, head);
  head->previous = new_node;
  head = new_node;
  size++;
}

template <typename T>
void Double_List<T>::push_back(const T& value) {
  if (is_empty()) {
    head = new Node(value);
    tail = head;
    size++;
    return;
  }
  Node* new_node = new Node(value, nullptr, tail);
  tail->next = new_node;
  tail = tail->next;
  size++;
}

template <typename T>
T Double_List<T>::pop_front() {
  if (is_empty()) {
    throw std::logic_error("empty");
  }
  T copy = head->data;
  if (size == 1) {
    delete head;
    head = nullptr;
    tail = nullptr;
    size--;
    return copy;
  }
  Node* prev_head = head;
  head = head->next;
  head->previous = nullptr;
  delete prev_head;
  size--;
  return copy;
}

template <typename T>
T Double_List<T>::pop_back() {
  if (is_empty()) {
    throw std::logic_error("empty");
  }
  T copy = tail->data;
  if (size == 1) {
    delete tail;
    head = nullptr;
    tail = nullptr;
    size--;
    return copy;
  }
  Node* prev_tail = tail->previous;
  prev_tail->next = nullptr;
  delete tail;
  tail = prev_tail;
  size--;
  return copy;
}

template <typename T>
typename Double_List<T>::Node* Double_List<T>::find(const T& value) {
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
typename Double_List<T>::Node* Double_List<T>::insert(const T& value, Node* pos) {
  if (pos == nullptr) {
    throw std::invalid_argument("nullptr");
  }
  if (pos == head) {
    push_front(value);
    return head;
  }
  Node* current = pos->previous;
  Node* new_node = new Node(value, pos, current);
  pos->previous = new_node;
  current->next = new_node;
  size++;
  return new_node;
}

template <typename T>
typename Double_List<T>::Node* Double_List<T>::insert(const T& value, size_t index) {
  if (index > size) {
    throw std::out_of_range("not in range");
  }
  if (index == 0) {
    push_front(value);
    return head;
  }
  if (index == size) {
    push_back(value);
    return tail;
  }
  if ( index < size / 2) {
    Node* current_on_index = head;
    for (size_t i = 0; i < index; i++) {
      current_on_index = current_on_index->next;
    }
    return insert(value, current_on_index);
  }
  if ( index >= size / 2) {
    Node* current_on_index = tail;
    for (size_t i = size - 1; i > index; i--) {
      current_on_index = current_on_index->previous;
    }
    return insert(value, current_on_index);
  }
}


template <typename T>
T Double_List<T>::erase(Node* pos) {
  if (pos == nullptr) {
    throw std::invalid_argument("nullptr");
  }
  if (pos == head) {
    return pop_front();
  }
  if (pos == tail) {
    return pop_back();
  }
  T copy = pos->data;
  pos->previous->next = pos->next;
  pos->next->previous = pos->previous;
  delete pos;
  size--;
  return copy;
}

template <typename T>
T Double_List<T>::erase(size_t index) {
  if (index >= size) {
    throw std::out_of_range("out of size");
  }
  if (index == 0) {
    return erase(head);
  }
  if (index == size - 1){
    return erase(tail);
  }
  if (index < size / 2) {
    Node* current = head;
    for (size_t i = 0; i < index; i++) {
      current = current->next;
    }
    return erase(current);
  }
  if (index >= size / 2) {
    Node* current = tail;
    for (size_t i = size - 1; i > index; i--) {
      current = current->previous;
    }
    return erase(current);
  }
}

#endif  // LIB_LIST_DOUBLE_LIST_H_
