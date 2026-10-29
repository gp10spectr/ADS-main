#include <cstddef>
#include <iostream>
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
	//size?

	void repack();
public:
	Multi_Stack(size_t, size_t);	//N, size
	//Multi_Stack(size_t);			//try?
	Multi_Stack(const Multi_Stack&);
	Multi_Stack(Multi_Stack&&) noexcept;
	~Multi_Stack();

	size_t get_size() const noexcept;
	T& get_top(size_t);
	void push(size_t, const T&);
	T pop(size_t);
	bool is_full() const noexcept;
	bool is_empty() const noexcept;
	bool is_empty_single() const noexcept;
	bool is_full_single() const noexcept;

};

template <typename T>
Multi_Stack<T>::Multi_Stack(size_t stack_count = 1, size_t s = 1) {
	N = stack_count;
	count = 0;
	data = new T[s];
	lv = new size_t[N];
	rv = new size_t[N];
	tops = new size_t[N];
}

template <typename T>
Multi_Stack<T>::Multi_Stack(const Multi_Stack& other) {
	size = other.size;
	N = other.N;
	count = other.count;
	for (size_t i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
	for (size_t i = 0; i < N / 2; i++) {
		lv[i] = other.lv[i];
	}
	for (size_t i = 0; i < N / 2; i++) {
		rv[i] = other.rv[i];
	}
	for (size_t i = 0; i < N; i++) {
		tops[i] = other.tops[i];
	}
}

template <typename T>
Multi_Stack<T>::Multi_Stack(Multi_Stack&& other) noexcept {
	data = std::move(other.data);
	lv = std::move(other.lv);
	rv = std::move(other.rv);
	tops = std::move(other.tops);
	size = other.size;
	N = other.N;
	count = other.count;
	other.size = 0;
	other.N = 0;
	other.count = 0;
	data = nullptr;
	lv = nullptr;
	rv = nullptr;
	tops = nullptr;
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
size_t Multi_Stack<T>::get_size() const noexcept {
	return size;
}

template <typename T>
T& Multi_Stack<T>::get_top(size_t stack_count) {
	return data[tops[stack_count]];
}

template <typename T>
void Multi_Stack<T>::push(size_t stack_count, const T& value) {
	tops[stack_count]++;
	data[tops[stack_count]] = value;
	count++;
}

template <typename T>
T Multi_Stack<T>::pop(size_t stack_count) {
	tops[stack_count]--;
	count--;
}

template <typename T>
bool Multi_Stack<T>::is_full() const noexcept {
	return (count == size);
}

template <typename T>
bool Multi_Stack<T>::is_empty() const noexcept {
	return (count == 0);
}

