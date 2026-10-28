#include <cstddef>
#include <exception>
#include <iostream>

template <typename T>
class Queue;

template <typename T>
class Queue {
private:
	size_t size;
	T* data;
	size_t front;
	size_t back;
	size_t count;
public:
	Queue(size_t);
	Queue(const Queue&);
	~Queue();

	size_t get_size() const noexcept;
	T& get_front();
	bool is_full() const noexcept;
	bool is_empty() const noexcept;
	void push(const T&);
	T pop();

};

template <typename T>
Queue<T>::Queue(size_t s) {
	size = s;
	front = 0;
	back = 0;
	count = 0;
	data = new T[s];
}

template <typename T>
Queue<T>::Queue(const Queue& other) {
	size = other.size;
	front = other.front;
	back = other.back;
	count = other.count;
	data = new T[other.size];
	for (size_t i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template <typename T>
Queue<T>::~Queue() {
	delete[] data;
	size = 0;
	front = 0;
	back = 0;
	count = 0;
}

template <typename T>
size_t Queue<T>::get_size() const noexcept {
	return size;
}

template <typename T>
bool Queue<T>::is_full() const noexcept {
	return count == size;
}

template <typename T>
bool Queue<T>::is_empty() const noexcept {
	return count == 0;
}

template <typename T>
void Queue<T>::push(const T& value) {
	if (is_full()) {
		throw std::out_of_range("full");
	}
	data[back] = value;
	back = (back + 1) % size;
}

template <typename T>
T Queue<T>::pop() {
	T tmp = data[front];
	front = (front + 1) % size;
	return tmp;
}

template <typename T>
T& Queue<T>::get_front() {
	if (size == 0) {
		throw std::out_of_range("empty");
	}
	return data[front];
}