#include <istream>

template <typename T>
class ArrayStack {
private:
	T* data;
	size_t currSize;
	size_t cap;

	void free();
	void copyFrom(const ArrayStack<T>& other);
	void resize(size_t newCap);

public:
	ArrayStack();
	ArrayStack(const ArrayStack<T>& other);
	ArrayStack<T>& operator=(const ArrayStack<T>& other);
	~ArrayStack();

	void push(const T& newEl);
	void pop();
	const T& peek() const;

	size_t size() const;
	bool isEmpty() const;
};

template <typename T>
ArrayStack<T>::ArrayStack():currSize(0),cap(4) {
	data = new T[cap];
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other) {
	copyFrom(other);
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
	free();
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other) {
	if (this != &other) {
		free();
		copy(other);
	}
	return *this;
}

template <typename T>
void ArrayStack<T>::free() {
	delete[] data;
	data = nullptr;
}

template <typename T>
void ArrayStack<T>::copyFrom(const ArrayStack<T>& other) {
	data = new T[other.cap];
	for (int i = 0;i < other.currSize;i++) {
		data[i] = other.data[i];
	}

	currSize = other.currSize;
	cap = other.cap;
}

template <typename T>
void ArrayStack<T>::resize(size_t newCap) {
	T* temp = data;
	data = new T[newCap];

	for (size_t i = 0;i < currSize;i++)
		data[i] = temp[i];

	cap = newCap;
	delete[] temp;
}


template <typename T>
void ArrayStack<T>::push(const T& newEl) {
	if (currSize >= cap)
		resize(cap * 2);
	data[currSize++] = newEl;
}

template <typename T>
void ArrayStack<T>::pop() {
	if (isEmpty())
		throw std::runtime_error("stack empty");
	T el = data[--currSize];

	if (currSize * 2 <= cap && cap > 1)
		resize(cap / 2);
}

template <typename T>
const T& ArrayStack<T>::peek() const {
	if (isEmpty())
		throw std::runtime_error("stack empty");
	return data[currSize - 1];
}

template <typename T>
size_t ArrayStack<T>::size() const {
	return currSize;
}

template <typename T>
bool ArrayStack<T>::isEmpty() const {
	return size() == 0;
}